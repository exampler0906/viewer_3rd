/********************************************************************

  RescueUOM.h

  Table-like access to UOM conversion tables.

  Rod Hanks,  Nov 15 2007

*********************************************************************/
#ifndef RescueUOM_H
#define RescueUOM_H

#include "myHeaders.h"

class RescueUOM
{
public:
  typedef enum {NONE,FACTOR,FRACTION,FORMULA} ConversionTypes;

  static RESCUEBOOL IsPer(const RESCUECHAR *pos);
  static RESCUEBOOL IsIES(const RESCUECHAR *pos);
  static int CompareUOM(const RESCUECHAR *name1, const RESCUECHAR *name2);
  static RESCUEINT32 IndexFromName(const RESCUECHAR *name);

  struct UOM
  {
    const RESCUECHAR *name;
    const RESCUECHAR *quantityTypeArray[13];
    RESCUEINT32 quantityTypeCount;
    RESCUEINT32 baseUnit;
    ConversionTypes conversionType;
    RESCUEDOUBLE conversion_A;
    RESCUEDOUBLE conversion_B;
    RESCUEDOUBLE conversion_C;
    RESCUEDOUBLE conversion_D;
  };

  static UOM uom[];

  static RESCUEINT32 UOMCount() {return 1230;}
  static const RESCUECHAR *Name(RESCUEINT32 zeroBasedNdx);
  static RESCUEBOOL IsBase(RESCUEINT32 zeroBasedNdx);
  static const RESCUECHAR **QuantityTypeArray(RESCUEINT32 zeroBasedNdx);
  static RESCUEINT32 QuantityTypeCount(RESCUEINT32 zeroBasedNdx);
  static RESCUEINT32 BaseUnitIndex(RESCUEINT32 zeroBasedNdx);
  static ConversionTypes ConversionType(RESCUEINT32 zeroBasedNdx);
  static RESCUEDOUBLE ConversionFactor(RESCUEINT32 zeroBasedNdx);
  static RESCUEDOUBLE ConversionNumerator(RESCUEINT32 zeroBasedNdx);
  static RESCUEDOUBLE ConversionDenominator(RESCUEINT32 zeroBasedNdx);
  static RESCUEDOUBLE Conversion_A(RESCUEINT32 zeroBasedNdx);
  static RESCUEDOUBLE Conversion_B(RESCUEINT32 zeroBasedNdx);
  static RESCUEDOUBLE Conversion_C(RESCUEINT32 zeroBasedNdx);
  static RESCUEDOUBLE Conversion_D(RESCUEINT32 zeroBasedNdx);
private:
  static RESCUEINT32 IndexFromName_1(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_a(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_b(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_c(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_d(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_e(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_f(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_g(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_h(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_i(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_j(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_k(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_l(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_m(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_n(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_o(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_p(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_r(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_s(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_t(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_u(const RESCUECHAR *name);
  static RESCUEINT32 IndexFromName_w(const RESCUECHAR *name);
};

#endif

