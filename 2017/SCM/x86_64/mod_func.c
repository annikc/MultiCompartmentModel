#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;
modl_reg(){
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");

    fprintf(stderr," ../_mods//CClamp.mod");
    fprintf(stderr," ../_mods//GABAa.mod");
    fprintf(stderr," ../_mods//HH.mod");
    fprintf(stderr," ../_mods//KCC2.mod");
    fprintf(stderr," ../_mods//KCC2_SA.mod");
    fprintf(stderr," ../_mods//cad.mod");
    fprintf(stderr," ../_mods//calH.mod");
    fprintf(stderr," ../_mods//calL.mod");
    fprintf(stderr," ../_mods//cat.mod");
    fprintf(stderr, "\n");
  }
  _CClamp_reg();
  _GABAa_reg();
  _HH_reg();
  _KCC2_reg();
  _KCC2_SA_reg();
  _cad_reg();
  _calH_reg();
  _calL_reg();
  _cat_reg();
}
