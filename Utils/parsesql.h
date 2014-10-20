// parsesql.h
//
//	class ParseException	- exception type
//	class ParseSQL			- Class of parse SQL query
//	class Condition			- Class for writing and receiving conditions as a string
//		class Condition_Qracle		- Condition for Oracle
//		class Condition_MSSQLServer	- Condition for MS SQL Server
//		class Condition_MSJet		- Condition for Access
//	class vector_conditionptr - Class to manage the pointers to the conditions
///////////////
// Author: Ilya Zharkov; e-mail:izharkov@live.ru
// Creation date: 12.03.2003
// Date modified: 25.06.2003
//	+ Redesigned parser
//	+ Accounted "GROUP BY", "HAVING", "ORDER BY"
// Date modified: 25.03.2004
//	+ parsing the query is insensitive
//	+ added support for variables in the query
//		Ex.:
//			IAZSQL::ParseSQL parse(L"SELECT Column1, Column2 FROM T1 WHERE Column1>$param");
//			parse.AddVariable(L"param", L"'text'");
//			instead of $param will be substituted 'text'
// Date modified: 11.04.2006
//	* changed algorithm to search for variables in the query
///////////////

#pragma once

#include <vector>
#include <string>
#include <algorithm>

namespace IAZSQL
{

using std::vector;
using std::wstring;

class ParseException
{
public:
	ParseException(const wchar_t text[], long code=1) : m_text(text), m_code(code)
	{}
	ParseException(const ParseException& ex) : m_text(ex.m_text), m_code(ex.m_code)
	{
	}
	const wstring& Message() const
	{
		return m_text;
	}
	long ErrorCode() const
	{
		return m_code;
	}
private:
	ParseException& operator = (const ParseException& );
	const wstring m_text;
	long m_code;
};

//////////////////////////////////////////
// Change to upper case characters
//////////////////////////////////////////
inline void change_register(wchar_t& c)
{
	if (c>=97 && c<=122) c-=32;
}

inline void ChangeRegister(wstring& text)
{
	std::for_each(text.begin(), text.end(), change_register);
}

//////////////////////////////////////////
// Class of parse SQL query
//////////////////////////////////////////
class ParseSQL
{
public:
	typedef vector<wstring> StringVector;
	ParseSQL(const wstring& sql) : m_SQL(sql), m_OriginalSQL(m_SQL),
		m_blankSimbols(L" \t\r\n\b"),
		m_varSimbols(L"_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")
	{
		ChangeRegister(m_SQL);
		assert(Find_Select_From(m_iSelect, m_iFrom), L"SQL request is incorrect!");
	}
	ParseSQL(const wchar_t sql[]) : m_SQL(sql), m_OriginalSQL(m_SQL),
		m_blankSimbols(L" \t\r\n\b"),
		m_varSimbols(L"_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")
	{
		ChangeRegister(m_SQL);
		assert(Find_Select_From(m_iSelect, m_iFrom), L"SQL request is incorrect!");
	}

// Returns a list of columns involved in the query
	void GetNameColumns(StringVector& columns) const
	{
		//ATLASSERT(m_iSelect!=wstring::npos && m_iFrom!=wstring::npos);
		size_t iSelect=m_iSelect;
		while (iSelect<m_iFrom)
		{
			size_t iComma=m_SQL.find(L',', iSelect);
			while ((iComma!=wstring::npos && iComma<m_iFrom) &&
					FindBreaks(iComma, iSelect))
			{
				iComma=m_SQL.find(L',', iComma+1);
			}
			if (iComma==wstring::npos || iComma>m_iFrom) iComma=m_iFrom;
			const size_t iAS=m_SQL.rfind(L"AS", iComma-1);
			if (iAS!=wstring::npos && iSelect<iAS &&
				iAS+2 < m_SQL.length() &&
				m_blankSimbols.find(m_SQL[iAS+2])!=wstring::npos)
			{
				iSelect=iAS+2; // "AS"
			}
			wstring col=m_SQL.substr(iSelect, iComma-iSelect).c_str();
			//col.TrimRight(L" \n\r\b\t");
			//col.TrimLeft(L" \n\r\b\t");
			columns.push_back(col);
			iSelect=iComma+1;
		}
	}

// Adds a condition to the query
	void AddCondition(const wstring& condition)
	{
		//ATLASSERT(m_iSelect!=wstring::npos && m_iFrom!=wstring::npos);

		if (condition.empty()) return;

		wstring cnd=condition;
		ChangeRegister(cnd);

		// erase all of the first 'unneeded' characters
		const size_t iChar=cnd.find_first_not_of(L' ');
		cnd.erase(0, iChar);
		// The first character must be "AND" or "OR "
		{
		const wstring first_simbs=cnd.substr(0, 3);
		assert(first_simbs==L"AND" || first_simbs==L"OR ", L"Condition is incorrect! The first character must be \"AND\" or \"OR\".");
		}

		size_t iWhere, iBegin;
		if (!Find_Where(m_iFrom+5, iBegin, iWhere))
		{
			// skip "AND" or "OR "
			// and look for the first non-blank
			const size_t iChar=cnd.find_first_not_of(L' ', 3);
			// erase all of the first 'unneeded' characters
			cnd.erase(0, iChar);
			if (!cnd.empty())
			{
				m_OriginalSQL.insert(iWhere, L" WHERE " + cnd);
			}
		}
		else
		{
			m_OriginalSQL.insert(iWhere, L" " + condition);
		}
	// need to m_SQL and m_OriginalSQL match up to the register
		ChangeRegister(m_SQL=m_OriginalSQL);
	}

//	Replaces the $variable to the value in SQL query
	void AddVariable(const wstring& variable, const wstring& value)
	{
		check_variable(variable);
		const wstring var=L"$"+variable;
		size_t iVar=0;
		while ((iVar=m_OriginalSQL.find(var, iVar))!=wstring::npos)
		{
			if ((iVar+var.length() < m_OriginalSQL.length() &&
				m_varSimbols.find(m_OriginalSQL[iVar+var.length()])==wstring::npos) ||
				iVar+var.length() == m_OriginalSQL.length())
			{
				m_OriginalSQL.replace(iVar, var.length(), value);
				iVar+=value.length();
			}
			else
				iVar+=var.length();
		}
	// need to m_SQL and m_OriginalSQL match up to the register
		ChangeRegister(m_SQL=m_OriginalSQL);
	}

// deleting all variables
	void RemoveVariables()
	{
		size_t iVar=0;
		while ((iVar=m_OriginalSQL.find(L'$', iVar)) != wstring::npos)
		{
			const size_t iVar_end=m_OriginalSQL.find_first_not_of(m_varSimbols, iVar+1);
			if (iVar_end==wstring::npos)
			{
				m_OriginalSQL.erase(iVar, m_OriginalSQL.size());
				break;
			}
			else
			{
				m_OriginalSQL.erase(iVar, iVar_end-iVar);
			}
		}
	// need to m_SQL and m_OriginalSQL match up to the register
		ChangeRegister(m_SQL=m_OriginalSQL);
	}

	template<class TString>
	TString SQL() const
	{
		return TString(m_OriginalSQL.c_str());
	}
	template<> const wstring& SQL() const
	{
		return m_OriginalSQL;
	}

private:
// Search section SELECT ... FROM
// iSelect == is first simbol after 'SELECT'
// iFrom   == is first simbol after 'FROM'
	bool Find_Select_From(size_t& iSelect, size_t& iFrom) const
	{
		iSelect = m_SQL.find(L"SELECT");
		if (iSelect == wstring::npos)
		{
			iFrom=iSelect = wstring::npos;
			return false;
		}
		iSelect+=6; // shifted to the end 'SELECT'
		return Find_Keyword(iSelect, L"FROM", iFrom);
	}

// Search for 'WHERE' starting position iStart
// iBegin, iEnd - is beginning and end section
	bool Find_Where(const size_t iStart, size_t& iBegin, size_t& iEnd) const
	{
		if (!Find_Keyword(iStart, L"WHERE", iBegin))
		{
			iBegin=iStart;
		}
		else iBegin+=5; // length 'WHERE'
		if (!Find_Keyword(iBegin, L"GROUP BY", iEnd))
		{
			if (!Find_Keyword(iBegin, L"HAVING", iEnd))
			{
				Find_Keyword(iBegin, L"ORDER BY", iEnd);
			}
		}
		if (iEnd==wstring::npos)
			iEnd=m_SQL.length();
		else
			--iEnd; // get up on the previous character
		if (iBegin == iStart)
		{
			iBegin=iEnd; // section 'WHERE' was not found
			return false;
		}
		return true;
	}

// search for "keyword" from position iStart
// iKeyword - is beginning of the word
	bool Find_Keyword(const size_t iStart, const wstring& keyword, size_t& iKeyword) const
	{
		const size_t length=keyword.length();
		iKeyword = iStart-length;
		do
		{
			iKeyword = m_SQL.find(keyword, iKeyword+length);
			if (iKeyword == wstring::npos)
				return false;
		} while (FindBreaks(iKeyword, iStart));
		return true;
	}

// determine is whether or not the current character (iPos) in parentheses
// limit_left - is lower limit on the search of the brackets (for acceleration)
	bool FindBreaks(const size_t iPos, const size_t limit_left) const
	{
		int countBr=0;
		for (size_t i=iPos-1; i>limit_left; --i)
		{
			if (m_SQL[i]==L')')		++countBr;
			else
				if (m_SQL[i]==L'(')	--countBr;
			if (countBr<0) return true;
		}
		return false;
	}
	void check_variable(const wstring& variable)
	{
		assert(variable.length()>0 &&
			variable.find_first_not_of(m_varSimbols)==wstring::npos &&
			m_varSimbols.substr(m_varSimbols.length()-10).find(variable[0])==wstring::npos,
			L"Variable name is not correct!");
	}
	static void assert(bool b, const wchar_t text_error[])
	{
		//ATLASSERT(b);
		if (!b) throw ParseException(text_error);
	}
	
	ParseSQL& operator = (const ParseSQL& );

///// Atributes //////
	wstring			m_SQL, m_OriginalSQL;
	size_t			m_iSelect, m_iFrom; // position "SELECT" & "FROM"
	const wstring	m_blankSimbols, m_varSimbols;
};

} // namespace IAZSQL
