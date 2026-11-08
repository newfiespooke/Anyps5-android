#include "prx/libSceLibreSsl3/libSceLibreSsl3.hpp"
#include <cstddef>
#include <cstdio>
#include <source_location>
#include <cstdlib>
#include <stdexcept>

namespace {
void Require(bool condition, std::source_location location = std::source_location::current()) {
    if (condition) return;
    std::fprintf(stderr, "LibreSSL3 X509 public-key accessor check failed at line %u\n", location.line());
    std::abort();
}
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

int main() {
    LibreSsl3EvpPkey pkey{};
    LibreSsl3X509Pubkey publicKey{};
    publicKey.pkey = &pkey;
    CertInfo info{};
    info.key = &publicKey;
    LibreSsl3X509 certificate{};
    certificate.certInfo = reinterpret_cast<LibreSsl3X509CertInfo*>(&info);

    Require(X509_get_X509_PUBKEY_nid_postfix(&certificate) == &publicKey);
    Require(X509_get0_pubkey_nid_postfix(&certificate) == &pkey);
    publicKey.pkey = nullptr;
    Require(X509_get0_pubkey_nid_postfix(&certificate) == nullptr);
    LibreSsl3Asn1String encoded{};
    publicKey.publicKey = &encoded;
    bool threw = false;
    try { X509_get0_pubkey_nid_postfix(&certificate); } catch (const std::runtime_error&) { threw = true; }
    Require(threw);
    publicKey.publicKey = nullptr;
    info.key = nullptr;
    Require(X509_get_X509_PUBKEY_nid_postfix(&certificate) == nullptr);
    Require(X509_get0_pubkey_nid_postfix(&certificate) == nullptr);
    Require(X509_get_X509_PUBKEY_nid_postfix(nullptr) == nullptr);
    Require(X509_get0_pubkey_nid_postfix(nullptr) == nullptr);
    std::puts("libSceLibreSsl3 X509 public-key accessor tests passed");
}
