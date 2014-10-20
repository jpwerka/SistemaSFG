unit uSfgDinForms;

interface

uses
  Windows, Classes, Controls, Forms;

procedure SfgCreateForm(AOwner: TComponent; InstanceClass: TComponentClass; var Reference);

implementation

procedure SfgCreateForm(AOwner: TComponent; InstanceClass: TComponentClass; var Reference);
var
  Instance: TComponent;
begin
  Instance := TComponent(InstanceClass.NewInstance);
  TComponent(Reference) := Instance;
  try
    Instance.Create(AOwner);
  except
    TComponent(Reference) := nil;
    raise;
  end;
end;
end.

 