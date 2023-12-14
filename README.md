# My Space

The repository contains shared config for Vim and Neovim.
Before proceeding, back up your existing Vim configuration if you need because it will be replaced with the one in this repo.

## Clone this repository recursively

```
git clone --recursive git@github.com:Daljeetone/dljthomeconfig.git
```

## Get the latest Vim/NeoVim version

The language server plugin (coc.nvim) needs vim >= `8.1.1719` and neovim >= `0.4.3` to support features like popup and text property.

## Copy configuration files, download and install utilities (fzf, nodejs, etc.) required by language server

```
./install-tools.sh
```

## Install Language Server Extensions for Vim (On demand)

For each language server you want to use, install the coc plugin for it.

Open Vim and execute:

### C/C++

`:CocInstall coc-clangd`  # Install clangd-plugin

Open any .c or .cpp file and execute the following command (It is imperative to open a source file, refer: <https://github.com/clangd/coc-clangd/issues/61>)

`:CocCommand clangd.install`  # Install clangd

### Go
`:CocInstall coc-go`

### Rust
`:CocInstall coc-rls`

### Other languages

Just try `:CocInstall coc-<language_name>`, and it will most likely work.

## Usage

You can use the following key-combinations, regardless of the language of the program

| Key | Action |
| ---------- | ---------- |
| `ctrl` + `f` | Find files (fuzzy) |
| `g` + `d` | Go to definition |
| `g` + `r` | Go to references |
| `ctrl` + `o` | Go back |
| `ctrl` + `i` | Go forward |
| `space` + `s` | Search for symbol (fuzzy) |
| `ctrl` + `a` | Grep |
| `<F8>` | Open/Close Sidebar with Symbols |

