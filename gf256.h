#ifndef __GF256__H__
#define __GF256__H__
#define _gf_m   8
#define _gf_q   256
#define _gf_msb 128
#define _gf_qm1 255
#define _gf_px  11d

typedef unsigned elemtype;
typedef int logtype;

extern elemtype gfalog[];
extern logtype gflog[];

#define gfadd(x,y)    ((x)^(y))
#define gfmulnz(x,y)  (gfalog[(gflog[x]+gflog[y])%(_gf_qm1)])
#define gfmul(x,y)    (((x)*(y))?(gfmulnz(x,y)):(0))
#define gfinvnz(x)    (gfalog[_gf_qm1-gflog[x]])
#define gfinv(x)      ((x)?(gfinvnz(x)):(0))
#define gfpownz(x,k)  (gfalog[(_gf_qm1+(((k) * gflog[x])%(_gf_qm1)))%_gf_qm1])
#define gfpow(x, k)   ((x)?(gfpownz(x,k)):((k)?0:gfalog[0]))

#endif
