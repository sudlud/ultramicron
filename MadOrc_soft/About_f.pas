unit About_f;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, pngimage, ExtCtrls, Registry, iaRS232;

type
  TAbout = class(TForm)
    Label1: TLabel;
    Image1: TImage;
    Button1: TButton;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Edit1: TEdit;
    Label6: TLabel;
    Edit2: TEdit;
    Label7: TLabel;
    Timer1: TTimer;
    Edit3: TEdit;
    Edit4: TEdit;
    Edit5: TEdit;
    Edit6: TEdit;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  About: TAbout;

implementation

{$R *.dfm}
uses main;

procedure TAbout.Button1Click(Sender: TObject);
var
  reg: TRegistry;
  vAns: TiaBuf;
  tmp: uint32;
begin
try
   if Edit3.Text <> '' then
   if Edit4.Text <> '' then
   if Edit5.Text <> '' then
   if Edit6.Text <> '' then
    begin
      if (mainFrm.RS232.Active = false) then
       begin
        mainFrm.RS232.Properties.PortNum  := comport_number;
        mainFrm.RS232.Properties.BaudRate := CBR_115200;
        mainFrm.RS232.Properties.Parity   := NOPARITY;
        mainFrm.RS232.Properties.StopBits := ONESTOPBIT;
        mainFrm.RS232.Open;
        mainFrm.RS232.StartListner;
        if (mainFrm.RS232.Active)then
        begin
         DevPresent:=true;
         SetLength(vAns, 5);

         vAns[0]:=$e3;

         tmp:=        StrToInt('$'+Copy(Edit3.Text, 5, 3));
         tmp:=    tmp-StrToInt('$'+Copy(Edit3.Text, 3, 2));
         vAns[1]:=tmp-StrToInt('$'+Copy(Edit3.Text, 1, 2));

         tmp:=        StrToInt('$'+Copy(Edit4.Text, 5, 3));
         tmp:=    tmp-StrToInt('$'+Copy(Edit4.Text, 3, 2));
         vAns[2]:=tmp-StrToInt('$'+Copy(Edit4.Text, 1, 2));

         tmp:=        StrToInt('$'+Copy(Edit5.Text, 5, 3));
         tmp:=    tmp-StrToInt('$'+Copy(Edit5.Text, 3, 2));
         vAns[3]:=tmp-StrToInt('$'+Copy(Edit5.Text, 1, 2));

         tmp:=        StrToInt('$'+Copy(Edit6.Text, 5, 3));
         tmp:=    tmp-StrToInt('$'+Copy(Edit6.Text, 3, 2));
         vAns[4]:=tmp-StrToInt('$'+Copy(Edit6.Text, 1, 2));


//         vAns[1]:=StrToInt(Edit3.Text);
//         vAns[2]:=StrToInt(Edit4.Text);
//         vAns[3]:=StrToInt(Edit5.Text);
//         vAns[4]:=StrToInt(Edit6.Text);
         mainFrm.RS232.Send(vAns);
         sleep(100);
        end
        else
        begin
          if(DevPresent=true) then
          begin
            DevPresent:=false;
          end;
          mainFrm.RS232.StopListner;
          mainFrm.RS232.Close;
        end;
    end;
    mainFrm.RS232.StopListner;
    mainFrm.RS232.Close;
    end;
except
  on Exception : EConvertError do
    sleep(100);
  end;

  reg := TRegistry.Create;                               // Открываем реестр
  reg.RootKey := HKEY_CURRENT_USER;                      // Для текущего пользователя
  reg.OpenKey('Software\USB_Geiger\USB_Geiger', true); // Открываем раздел
  reg.WriteString('Reg_key', Edit1.Text);
  reg.CloseKey;                                          // Закрываем раздел
  reg.Free;
  About.Close;
end;


procedure TAbout.FormCreate(Sender: TObject);
var
  reg: TRegistry;
begin

  reg := TRegistry.Create;                              // Открываем реестр
  reg.RootKey := HKEY_CURRENT_USER;
  reg.OpenKey('Software\USB_Geiger\USB_Geiger', false);
  Edit1.Text := reg.ReadString('Reg_key');
  reg.CloseKey;                                          // Закрываем раздел
end;

procedure TAbout.Timer1Timer(Sender: TObject);
begin
 About_f.About.Edit2.Text := IntToHex(device_serial_0,8)+ ' ' +IntToHex(device_serial_1,8)+ ' ' +IntToHex(device_serial_2,8);
end;

end.
