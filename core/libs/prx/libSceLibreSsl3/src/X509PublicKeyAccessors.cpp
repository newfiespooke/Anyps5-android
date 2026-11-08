#include "prx/libSceLibreSsl3/include/Api.hpp"
#include "prx/libc/include/General.hpp"
#include <cstddef>

namespace {

struct CertInfo {
    void* version;
    void* serialNumber;
    void* signature;
    void* issuer;
    LibreSsl3X509Validity* validity;
    void* subject;
    LibreSsl3X509Pubkey* key;
};

static_assert(offsetof(CertInfo, key) == 48);

}

extern "C" {

void* APS5_VABI X509_get_X509_PUBKEY_nid_postfix(const LibreSsl3X509* certificate) {
    if (!certificate || !certificate->certInfo) return nullptr;
    return reinterpret_cast<const CertInfo*>(certificate->certInfo)->key;
}

void* APS5_VABI X509_get0_pubkey_nid_postfix(const LibreSsl3X509* certificate) {
    auto* key = static_cast<const LibreSsl3X509Pubkey*>(X509_get_X509_PUBKEY_nid_postfix(certificate));
    if (!key) return nullptr;
    if (!key->pkey && key->publicKey) NotImplemented_nid_no_patch("X509_get0_pubkey");
    return key->pkey;
}

}
