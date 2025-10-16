# Contributing

## Requirements

- Janet and jpm
- C compiler for the native module
- Optional: Nix

## Getting started

If you use Nix, create an `.envrc` file like this:
```text
use flake
path_add PATH ./jpm_tree/bin/
```

If you don't use Nix, you'll have to install Janet and jpm yourself.

Once setup, install the dependencies and run the tests, to verify everything works.

```shell
$ jpm install --local
$ jpm test
```
