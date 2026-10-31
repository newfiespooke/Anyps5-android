#include "prx/libSceLibcInternal/include/Api.hpp"
#include "prx/libc/include/Api.hpp"
#include "prx/libc/include/General.hpp"
#include "prx/libc/include/GuestLocale.hpp"
#include "SceTypes.hpp"

extern "C" {

char APS5_VABI sceLibcInternalNumpunctDoDecimalPoint_nid_no_patch(const GuestLocale::NumpunctFacet* self) {
    return NumpunctDoDecimalPoint_nid_no_patch(self);
}
APS5_EXPORT("JXzQGOtumdM", sceLibcInternalNumpunctDoDecimalPoint_nid_no_patch);

char APS5_VABI sceLibcInternalNumpunctDoThousandsSep_nid_no_patch(const GuestLocale::NumpunctFacet* self) {
    return NumpunctDoThousandsSep_nid_no_patch(self);
}
APS5_EXPORT("zv1EMhI7R1c", sceLibcInternalNumpunctDoThousandsSep_nid_no_patch);

GuestLocale::String* APS5_VABI sceLibcInternalNumpunctDoGrouping_nid_no_patch(GuestLocale::String* result, const GuestLocale::NumpunctFacet* self) {
    return NumpunctDoGrouping_nid_no_patch(result, self);
}
APS5_EXPORT("cnNz2ftNwEU", sceLibcInternalNumpunctDoGrouping_nid_no_patch);

GuestLocale::String* APS5_VABI sceLibcInternalNumpunctDoFalsename_nid_no_patch(GuestLocale::String* result, const GuestLocale::NumpunctFacet* self) {
    return NumpunctDoFalsename_nid_no_patch(result, self);
}
APS5_EXPORT("ozLi0i4r6ds", sceLibcInternalNumpunctDoFalsename_nid_no_patch);

GuestLocale::String* APS5_VABI sceLibcInternalNumpunctDoTruename_nid_no_patch(GuestLocale::String* result, const GuestLocale::NumpunctFacet* self) {
    return NumpunctDoTruename_nid_no_patch(result, self);
}
APS5_EXPORT("nRf0VQ++OEw", sceLibcInternalNumpunctDoTruename_nid_no_patch);

char APS5_VABI sceLibcInternalNumpunctDecimalPoint_nid_no_patch(const GuestLocale::NumpunctFacet* self) {
    return NumpunctDecimalPoint_nid_no_patch(self);
}
APS5_EXPORT("klWxQ2nKAHY", sceLibcInternalNumpunctDecimalPoint_nid_no_patch);

char APS5_VABI sceLibcInternalNumpunctThousandsSep_nid_no_patch(const GuestLocale::NumpunctFacet* self) {
    return NumpunctThousandsSep_nid_no_patch(self);
}
APS5_EXPORT("QGSIlqfIU2c", sceLibcInternalNumpunctThousandsSep_nid_no_patch);

GuestLocale::String* APS5_VABI sceLibcInternalNumpunctGrouping_nid_no_patch(GuestLocale::String* result, const GuestLocale::NumpunctFacet* self) {
    return NumpunctGrouping_nid_no_patch(result, self);
}
APS5_EXPORT("JWplGh2O0Rs", sceLibcInternalNumpunctGrouping_nid_no_patch);

GuestLocale::String* APS5_VABI sceLibcInternalNumpunctFalsename_nid_no_patch(GuestLocale::String* result, const GuestLocale::NumpunctFacet* self) {
    return NumpunctFalsename_nid_no_patch(result, self);
}
APS5_EXPORT("3+VwUA8-QPI", sceLibcInternalNumpunctFalsename_nid_no_patch);

GuestLocale::String* APS5_VABI sceLibcInternalNumpunctTruename_nid_no_patch(GuestLocale::String* result, const GuestLocale::NumpunctFacet* self) {
    return NumpunctTruename_nid_no_patch(result, self);
}
APS5_EXPORT("fXUuZEw7C24", sceLibcInternalNumpunctTruename_nid_no_patch);

}
