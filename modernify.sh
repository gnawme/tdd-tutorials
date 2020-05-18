#!/bin/bash
modernes=(   
"modernize-avoid-bind",
"modernize-avoid-c-arrays",
"modernize-concat-nested-namespaces",
"modernize-deprecated-headers",
"modernize-deprecated-ios-base-aliases",
"modernize-loop-convert",
"modernize-make-shared",
"modernize-make-unique",
"modernize-pass-by-value",
"modernize-raw-string-literal",
"modernize-redundant-void-arg",
"modernize-replace-auto-ptr",
"modernize-replace-random-shuffle",
"modernize-return-braced-init-list",
"modernize-shrink-to-fit",
"modernize-unary-static-assert",
"modernize-use-auto",
"modernize-use-bool-literals",
"modernize-use-default-member-init",
"modernize-use-emplace",
"modernize-use-equals-default",
"modernize-use-equals-delete",
"modernize-use-nodiscard",
"modernize-use-noexcept",
"modernize-use-nullptr",
"modernize-use-override",
"modernize-use-transparent-functors",
"modernize-use-uncaught-exceptions",
"modernize-use-using")

minus="-*,"

for check in ${modernes[@]}; do
    run-clang-tidy-9 -header-filter='.*' -checks=$minus$check -fix
done