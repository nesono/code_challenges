load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "guenther_kaese_linked_list",
    srcs = ["guenther_kaese_linked_list.cpp"],
)

cc_test(
    name = "guenther_kaese_isutf8",
    srcs = ["guenther_kaese_isutf8.cpp"],
)

cc_test(
    name = "leetcode_common",
    srcs = [
        "leetcode_000_common.cpp",
        "leetcode_000_common.h",
    ],
)

cc_test(
    name = "leetcode_002_add_two_numbers",
    srcs = [
        "leetcode_002_add_two_numbers.cpp",
    ],
    deps = [":leetcode_common"],
)

cc_test(
    name = "leetcode_003_longest_substring",
    srcs = [
        "leetcode_003_longest_substring.cpp",
    ],
    deps = [":leetcode_common"],
)

cc_test(
    name = "leetcode_005_longest_palindrome_substring",
    srcs = [
        "leetcode_005_longest_palindrome_substring.cpp",
    ],
    deps = [":leetcode_common"],
)

cc_test(
    name = "leetcode_006_zig_zag_conversion",
    srcs = [
        "leetcode_006_zig_zag_conversion.cpp",
    ],
    deps = [":leetcode_common"],
)

cc_test(
    name = "leetcode_007_reverse_integer",
    srcs = [
        "leetcode_007_reverse_integer.cpp",
    ],
    deps = [":leetcode_common"],
)

cc_test(
    name = "leetcode_053_sum",
    srcs = [
        "leetcode_053_sum.cpp",
    ],
    deps = [":leetcode_common"],
)

cc_test(
    name = "leetcode_070_climbing_stairs",
    srcs = [
        "leetcode_070_climbing_stairs.cpp",
    ],
    deps = [":leetcode_common"],
)

cc_test(
    name = "leetcode_063_unique_paths_ii",
    srcs = [
        "leetcode_063_unique_paths_ii.cpp",
    ],
    deps = [":leetcode_common"],
)

cc_test(
    name = "leetcode_121_best_time_to_sell_stock",
    srcs = [
        "leetcode_121_best_time_to_sell_stock.cpp",
    ],
    deps = [":leetcode_common"],
)

cc_test(
    name = "leetcode_1858_longest_word_with_all_prefixes",
    srcs = [
        "leetcode_1858_longest_word_with_all_prefixes.cpp",
    ],
    deps = [":leetcode_common"],
)

cc_test(
    name = "leetcode_2021-05-01_number_connected_components_graph",
    srcs = ["leetcode_2021-05-01_number_connected_components_graph.cpp"],
    deps = [":leetcode_common"],
)

cc_test(
    name = "ranges_sum_squares",
    srcs = [
        "ranges_sum_squares.cpp",
    ],
    deps = ["@rangev3//:range-v3"],
)
