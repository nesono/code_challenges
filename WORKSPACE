workspace(name = "code_challenges")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

############# GoogleTest/GoogleMock framework. Used by most unit-tests.
http_archive(
    name = "com_google_googletest",
    sha256 = "e61e3889bd5cc3e6bc1084d2108ecda2f110c0387ba88b394ffd16043a1d5709",
    strip_prefix = "googletest-f5e592d8ee5ffb1d9af5be7f715ce3576b8bf9c4",
    # Keep this URL in sync with ABSL_GOOGLETEST_COMMIT in ci/cmake_common.sh.
    urls = ["https://github.com/google/googletest/archive/f5e592d8ee5ffb1d9af5be7f715ce3576b8bf9c4.zip"],  # 2021-04-29T14:40:44Z
)

############# Google benchmark.
http_archive(
    name = "com_github_google_benchmark",
    sha256 = "a07789754963e3ea3a1e13fed3a4d48fac0c5f7f749c5065f6c30cd2c1529661",
    strip_prefix = "benchmark-7d0d9061d83b663ce05d9de5da3d5865a3845b79",
    urls = ["https://github.com/google/benchmark/archive/7d0d9061d83b663ce05d9de5da3d5865a3845b79.zip"],  # 2021-05-11T11:56:00Z
)

############## C++ rules for Bazel.
http_archive(
    name = "rules_cc",
    sha256 = "f3908cb40a6577ab0d1ef9e00052739bf69b4313fa7d20b4d61d4521ea67abf3",
    strip_prefix = "rules_cc-ab5395627c80e025e824bd005d41f96b20618b9d",
    urls = ["https://github.com/bazelbuild/rules_cc/archive/ab5395627c80e025e824bd005d41f96b20618b9d.zip"],  # 2021-05-10T15:35:04Z
)

# Hedron's Compile Commands Extractor for Bazel
# https://github.com/hedronvision/bazel-compile-commands-extractor
http_archive(
    name = "hedron_compile_commands",
    sha256 = "e6f49fa7e1b0f7cb80c797916f6693305a852cf51ab1bd5797061ece3039e212",
    strip_prefix = "bazel-compile-commands-extractor-13e135934b0f3bf1b71982e512cbe1cb11f6414f",

    # Replace the commit hash in both places (below) with the latest, rather than using the stale one here.
    # Even better, set up Renovate and let it do the work for you (see "Suggestion: Updates" in the README).
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/13e135934b0f3bf1b71982e512cbe1cb11f6414f.tar.gz",
    # When you first run this tool, it'll recommend a sha256 hash to put here with a message like: "DEBUG: Rule 'hedron_compile_commands' indicated that a canonical reproducible form can be obtained by modifying arguments sha256 = ..."
)

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")

hedron_compile_commands_setup()
