#if defined(_MSC_VER)
#define NOVA_EXPORT __declspec(dllexport)
#elif defined(__GNUC__)
#define NOVA_EXPORT __attribute__((visibility("default")))
#else
#define NOVA_EXPORT
#pragma warning Couldn't determine export semantics for compiler. Please open an issue, or better, a PR
#endif
