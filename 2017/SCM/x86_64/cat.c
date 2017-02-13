/* Created by Language version: 6.2.0 */
/* NOT VECTORIZED */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib.h"
#undef PI
 
#include "md1redef.h"
#include "section.h"
#include "md2redef.h"

#if METHOD3
extern int _method3;
#endif

#undef exp
#define exp hoc_Exp
extern double hoc_Exp();
 
#define _threadargscomma_ /**/
#define _threadargs_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define gcatbar _p[0]
#define ica _p[1]
#define minf _p[2]
#define hinf _p[3]
#define taum _p[4]
#define tauh _p[5]
#define m _p[6]
#define h _p[7]
#define cai _p[8]
#define cao _p[9]
#define Dm _p[10]
#define Dh _p[11]
#define gcat _p[12]
#define _g _p[13]
#define _ion_cai	*_ppvar[0]._pval
#define _ion_cao	*_ppvar[1]._pval
#define _ion_ica	*_ppvar[2]._pval
#define _ion_dicadv	*_ppvar[3]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 static int hoc_nrnpointerindex =  -1;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static int _hoc_KTF();
 static int _hoc_alpm();
 static int _hoc_alph();
 static int _hoc_betm();
 static int _hoc_beth();
 static int _hoc_efun();
 static int _hoc_ghk();
 static int _hoc_h2();
 static int _hoc_rates();
 static int _hoc_states();
 static int _mechtype;
extern int nrn_get_mechtype();
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range();
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 ret(1.);
}
 /* connect user functions to hoc names */
 static IntFunc hoc_intfunc[] = {
 "setdata_cat", _hoc_setdata,
 "KTF_cat", _hoc_KTF,
 "alpm_cat", _hoc_alpm,
 "alph_cat", _hoc_alph,
 "betm_cat", _hoc_betm,
 "beth_cat", _hoc_beth,
 "efun_cat", _hoc_efun,
 "ghk_cat", _hoc_ghk,
 "h2_cat", _hoc_h2,
 "rates_cat", _hoc_rates,
 "states_cat", _hoc_states,
 0, 0
};
#define KTF KTF_cat
#define _f_betm _f_betm_cat
#define _f_alpm _f_alpm_cat
#define _f_beth _f_beth_cat
#define _f_alph _f_alph_cat
#define alpm alpm_cat
#define alph alph_cat
#define betm betm_cat
#define beth beth_cat
#define efun efun_cat
#define ghk ghk_cat
#define h2 h2_cat
 extern double KTF();
 extern double _f_betm();
 extern double _f_alpm();
 extern double _f_beth();
 extern double _f_alph();
 extern double alpm();
 extern double alph();
 extern double betm();
 extern double beth();
 extern double efun();
 extern double ghk();
 extern double h2();
 /* declare global and static user variables */
#define eca eca_cat
 double eca = 140;
#define ki ki_cat
 double ki = 0.001;
#define tfi tfi_cat
 double tfi = 0.68;
#define tfa tfa_cat
 double tfa = 1;
#define tBase tBase_cat
 double tBase = 23.5;
#define usetable usetable_cat
 double usetable = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "usetable_cat", 0, 1,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "tBase_cat", "degC",
 "ki_cat", "mM",
 "gcatbar_cat", "mho/cm2",
 "ica_cat", "mA/cm2",
 0,0
};
 static double delta_t = 1;
 static double h0 = 0;
 static double m0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "tBase_cat", &tBase_cat,
 "ki_cat", &ki_cat,
 "tfa_cat", &tfa_cat,
 "tfi_cat", &tfi_cat,
 "eca_cat", &eca_cat,
 "usetable_cat", &usetable_cat,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(), nrn_init(), nrn_state();
 static void nrn_cur(), nrn_jacob();
 
static int _ode_count();
 /* connect range variables in _p that hoc is supposed to know about */
 static char *_mechanism[] = {
 "6.2.0",
"cat",
 "gcatbar_cat",
 0,
 "ica_cat",
 "minf_cat",
 "hinf_cat",
 "taum_cat",
 "tauh_cat",
 0,
 "m_cat",
 "h_cat",
 0,
 0};
 static Symbol* _ca_sym;
 
static void nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 14, _prop);
 	/*initialize range parameters*/
 	gcatbar = 0;
 	_prop->param = _p;
 	_prop->param_size = 14;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[0]._pval = &prop_ion->param[1]; /* cai */
 	_ppvar[1]._pval = &prop_ion->param[2]; /* cao */
 	_ppvar[2]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 
}
 static _initlists();
 static void _update_ion_pointer(Datum*);
 _cat_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("ca", -10000.);
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
  hoc_register_dparam_size(_mechtype, 4);
 	hoc_register_cvode(_mechtype, _ode_count, 0, 0, 0);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 cat /home/annik/Dropbox/msc/SciNet/2017/SCM/x86_64/cat.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96520.0;
 static double R = 8.3134;
 static double KTOMV = .0853;
 static double *_t_alph;
 static double *_t_beth;
 static double *_t_alpm;
 static double *_t_betm;
 static double _zfacm , _zfach ;
static int _reset;
static char *modelname = "t-type calcium channel with high threshold for activation";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
static rates();
static states();
 static double _n_betm();
 static double _n_alpm();
 static double _n_beth();
 static double _n_alph();
 
double h2 (  _lcai )  
	double _lcai ;
 {
   double _lh2;
 _lh2 = ki / ( ki + _lcai ) ;
   
return _lh2;
 }
 
static int _hoc_h2() {
  double _r;
   _r =  h2 (  *getarg(1) ) ;
 ret(_r);
}
 
double ghk (  _lv , _lci , _lco )  
	double _lv , _lci , _lco ;
 {
   double _lghk;
 double _lnu , _lf ;
 _lf = KTF ( _threadargscomma_ celsius ) / 2.0 ;
   _lnu = _lv / _lf ;
   _lghk = - _lf * ( 1. - ( _lci / _lco ) * exp ( _lnu ) ) * efun ( _threadargscomma_ _lnu ) ;
   
return _lghk;
 }
 
static int _hoc_ghk() {
  double _r;
   _r =  ghk (  *getarg(1) , *getarg(2) , *getarg(3) ) ;
 ret(_r);
}
 
double KTF (  _lcelsius )  
	double _lcelsius ;
 {
   double _lKTF;
 _lKTF = ( ( 25. / 293.15 ) * ( _lcelsius + 273.15 ) ) ;
   
return _lKTF;
 }
 
static int _hoc_KTF() {
  double _r;
   _r =  KTF (  *getarg(1) ) ;
 ret(_r);
}
 
double efun (  _lz )  
	double _lz ;
 {
   double _lefun;
 if ( fabs ( _lz ) < 1e-4 ) {
     _lefun = 1.0 - _lz / 2.0 ;
     }
   else {
     _lefun = _lz / ( exp ( _lz ) - 1.0 ) ;
     }
   
return _lefun;
 }
 
static int _hoc_efun() {
  double _r;
   _r =  efun (  *getarg(1) ) ;
 ret(_r);
}
 static double _mfac_alph, _tmin_alph;
 static _check_alph();
 static _check_alph() {
  static int _maktable=1; int _i, _j, _ix = 0;
  double _xi, _tmax;
  if (!usetable) {return;}
  if (_maktable) { double _x, _dx; _maktable=0;
   _tmin_alph =  - 150.0 ;
   _tmax =  150.0 ;
   _dx = (_tmax - _tmin_alph)/200.; _mfac_alph = 1./_dx;
   for (_i=0, _x=_tmin_alph; _i < 201; _x += _dx, _i++) {
    _t_alph[_i] = _f_alph(_x);
   }
  }
 }

 double alph(double _lv){ _check_alph();
 return _n_alph(_lv);
 }

 static double _n_alph(double _lv){ int _i, _j;
 double _xi, _theta;
 if (!usetable) {
 return _f_alph(_lv); 
}
 _xi = _mfac_alph * (_lv - _tmin_alph);
 _i = (int) _xi;
 if (_xi <= 0.) {
 return _t_alph[0];
 }
 if (_i >= 200) {
 return _t_alph[200];
 }
 return _t_alph[_i] + (_xi - (double)_i)*(_t_alph[_i+1] - _t_alph[_i]);
 }

 
double _f_alph (  _lv )  
	double _lv ;
 {
   double _lalph;
 _lalph = 1.6e-4 * exp ( - ( _lv + 57.0 ) / 19.0 ) ;
   
return _lalph;
 }
 
static int _hoc_alph() {
  double _r;
    _r =  alph (  *getarg(1) ) ;
 ret(_r);
}
 static double _mfac_beth, _tmin_beth;
 static _check_beth();
 static _check_beth() {
  static int _maktable=1; int _i, _j, _ix = 0;
  double _xi, _tmax;
  if (!usetable) {return;}
  if (_maktable) { double _x, _dx; _maktable=0;
   _tmin_beth =  - 150.0 ;
   _tmax =  150.0 ;
   _dx = (_tmax - _tmin_beth)/200.; _mfac_beth = 1./_dx;
   for (_i=0, _x=_tmin_beth; _i < 201; _x += _dx, _i++) {
    _t_beth[_i] = _f_beth(_x);
   }
  }
 }

 double beth(double _lv){ _check_beth();
 return _n_beth(_lv);
 }

 static double _n_beth(double _lv){ int _i, _j;
 double _xi, _theta;
 if (!usetable) {
 return _f_beth(_lv); 
}
 _xi = _mfac_beth * (_lv - _tmin_beth);
 _i = (int) _xi;
 if (_xi <= 0.) {
 return _t_beth[0];
 }
 if (_i >= 200) {
 return _t_beth[200];
 }
 return _t_beth[_i] + (_xi - (double)_i)*(_t_beth[_i+1] - _t_beth[_i]);
 }

 
double _f_beth (  _lv )  
	double _lv ;
 {
   double _lbeth;
 _lbeth = 1.0 / ( exp ( ( - _lv + 15.0 ) / 10.0 ) + 1.0 ) ;
   
return _lbeth;
 }
 
static int _hoc_beth() {
  double _r;
    _r =  beth (  *getarg(1) ) ;
 ret(_r);
}
 static double _mfac_alpm, _tmin_alpm;
 static _check_alpm();
 static _check_alpm() {
  static int _maktable=1; int _i, _j, _ix = 0;
  double _xi, _tmax;
  if (!usetable) {return;}
  if (_maktable) { double _x, _dx; _maktable=0;
   _tmin_alpm =  - 150.0 ;
   _tmax =  150.0 ;
   _dx = (_tmax - _tmin_alpm)/200.; _mfac_alpm = 1./_dx;
   for (_i=0, _x=_tmin_alpm; _i < 201; _x += _dx, _i++) {
    _t_alpm[_i] = _f_alpm(_x);
   }
  }
 }

 double alpm(double _lv){ _check_alpm();
 return _n_alpm(_lv);
 }

 static double _n_alpm(double _lv){ int _i, _j;
 double _xi, _theta;
 if (!usetable) {
 return _f_alpm(_lv); 
}
 _xi = _mfac_alpm * (_lv - _tmin_alpm);
 _i = (int) _xi;
 if (_xi <= 0.) {
 return _t_alpm[0];
 }
 if (_i >= 200) {
 return _t_alpm[200];
 }
 return _t_alpm[_i] + (_xi - (double)_i)*(_t_alpm[_i+1] - _t_alpm[_i]);
 }

 
double _f_alpm (  _lv )  
	double _lv ;
 {
   double _lalpm;
 _lalpm = 0.1967 * ( - 1.0 * _lv + 19.88 ) / ( exp ( ( - 1.0 * _lv + 19.88 ) / 10.0 ) - 1.0 ) ;
   
return _lalpm;
 }
 
static int _hoc_alpm() {
  double _r;
    _r =  alpm (  *getarg(1) ) ;
 ret(_r);
}
 static double _mfac_betm, _tmin_betm;
 static _check_betm();
 static _check_betm() {
  static int _maktable=1; int _i, _j, _ix = 0;
  double _xi, _tmax;
  if (!usetable) {return;}
  if (_maktable) { double _x, _dx; _maktable=0;
   _tmin_betm =  - 150.0 ;
   _tmax =  150.0 ;
   _dx = (_tmax - _tmin_betm)/200.; _mfac_betm = 1./_dx;
   for (_i=0, _x=_tmin_betm; _i < 201; _x += _dx, _i++) {
    _t_betm[_i] = _f_betm(_x);
   }
  }
 }

 double betm(double _lv){ _check_betm();
 return _n_betm(_lv);
 }

 static double _n_betm(double _lv){ int _i, _j;
 double _xi, _theta;
 if (!usetable) {
 return _f_betm(_lv); 
}
 _xi = _mfac_betm * (_lv - _tmin_betm);
 _i = (int) _xi;
 if (_xi <= 0.) {
 return _t_betm[0];
 }
 if (_i >= 200) {
 return _t_betm[200];
 }
 return _t_betm[_i] + (_xi - (double)_i)*(_t_betm[_i+1] - _t_betm[_i]);
 }

 
double _f_betm (  _lv )  
	double _lv ;
 {
   double _lbetm;
 _lbetm = 0.046 * exp ( - _lv / 22.73 ) ;
   
return _lbetm;
 }
 
static int _hoc_betm() {
  double _r;
    _r =  betm (  *getarg(1) ) ;
 ret(_r);
}
 
static int  states (  )  {
   rates ( _threadargscomma_ v ) ;
   m = m + _zfacm * ( minf - m ) ;
   h = h + _zfach * ( hinf - h ) ;
   
/*VERBATIM*/
        return 0;
  return 0; }
 
static int _hoc_states() {
  double _r;
   _r = 1.;
 states (  ) ;
 ret(_r);
}
 
static int  rates (  _lv )  
	double _lv ;
 {
   double _la ;
 _la = alpm ( _threadargscomma_ _lv ) ;
   taum = 1.0 / ( tfa * ( _la + betm ( _threadargscomma_ _lv ) ) ) ;
   minf = _la / ( _la + betm ( _threadargscomma_ _lv ) ) ;
   _zfacm = ( 1.0 - exp ( - dt / taum ) ) ;
   _la = alph ( _threadargscomma_ _lv ) ;
   tauh = 1.0 / ( tfi * ( _la + beth ( _threadargscomma_ _lv ) ) ) ;
   hinf = _la / ( _la + beth ( _threadargscomma_ _lv ) ) ;
   _zfach = ( 1.0 - exp ( - dt / tauh ) ) ;
    return 0; }
 
static int _hoc_rates() {
  double _r;
   _r = 1.;
 rates (  *getarg(1) ) ;
 ret(_r);
}
 
static int _ode_count(_type)int _type; { hoc_execerror("cat", "cannot be used with CVODE");}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 0, 1);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 1, 2);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 2, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 3, 4);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  h = h0;
  m = m0;
 {
   rates ( _threadargscomma_ v ) ;
   m = minf ;
   h = hinf ;
   gcat = gcatbar * m * m * h * h2 ( _threadargscomma_ cai ) ;
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
  cai = _ion_cai;
  cao = _ion_cao;
 initmodel();
 }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   gcat = gcatbar * m * m * h * h2 ( _threadargscomma_ cai ) ;
   ica = gcat * ghk ( _threadargscomma_ v , cai , cao ) ;
   }
 _current += ica;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
  cai = _ion_cai;
  cao = _ion_cao;
 _g = _nrn_current(_v + .001);
 	{ double _dica;
  _dica = ica;
 _rhs = _nrn_current(_v);
  _ion_dicadv += (_dica - ica)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ica += ica ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type){
 double _break, _save;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 _break = t + .5*dt; _save = t;
 v=_v;
{
  cai = _ion_cai;
  cao = _ion_cao;
 { {
 for (; t < _break; t += dt) {
 error =  states();
 if(error){fprintf(stderr,"at line 56 in file cat.mod:\n	SOLVE states\n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 } }}

}

static terminal(){}

static _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
   _t_alph = makevector(201*sizeof(double));
   _t_beth = makevector(201*sizeof(double));
   _t_alpm = makevector(201*sizeof(double));
   _t_betm = makevector(201*sizeof(double));
_first = 0;
}
