# AMR

This project is develop as ...

## Architecture

Hexagonal Architecture layers

## Patterns

* Proxies
* Adapters
* Debouncer
* Interruption
* Hardware Abstration Layer (HAL)

## Quality attributes

***TBD***



> NOTES:
>
> For cyclomatic metric run:
>
> ```shell
> lizard -l cpp . -x"./Drivers/*" -x"./Debug/*" -x"./Core/*"
> ```
>
> For line number and other:
>
> ```shell
> scc --cocomo-project-type organic --ci -c .\Application\ .\Patterns\
> ```
