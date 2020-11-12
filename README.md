# My Space

The repository contains shared config for Vim and Neovim.
Before proceeding, back up your existing Vim configuration if you need because it will be replaced with the one in this repo.

## Clone this repository recursively

```
git clone --recursive git@github.com:Daljeetone/dljthomeconfig.git
```

## Get the latest Vim/NeoVim version

The language server plugin (coc.nvim) needs vim >= `8.1.1719` and neovim >= `0.4.3` to support features like popup and text property.

Currently, Ubuntu 18:04 does not have the required minimum version of Vim/Neovim in its PPA repositories and therefore we need to install it manually. I prefer Neovim over regular Vim, so the instructions to install latest Neovim are as follows:

```
git clone https://github.com/neovim/neovim.git

cd neovim

sudo apt install gperf luajit luarocks libuv1-dev libluajit-5.1-dev libunibilium-dev libmsgpack-dev libtermkey-dev libvterm-dev libutf8proc-dev

sudo luarocks build mpack
sudo luarocks build lpeg
sudo luarocks build inspect

make CMAKE_BUILD_TYPE=RelWithDebInfo
sudo make install

sudo update-alternatives --install /usr/bin/vi vi $(which nvim) 60
sudo update-alternatives --config vi
sudo update-alternatives --install /usr/bin/vim vim $(which nvim) 60
sudo update-alternatives --config vim
sudo update-alternatives --install /usr/bin/editor editor $(which nvim) 60
sudo update-alternatives --config editor
```

## Copy configuration files, download and install utilities (fzf, nodejs, etc.) required by language server

```
./install-tools.sh
```

## Install the Vim plugins

Open Vim and execute the following command, do not worry about the errors that show up when opening Vim.
```
:PluginInstall
```

## Install Language Server Extensions for Vim (On demand)

For each language server you want to use, install the coc plugin for it.

Open Vim and execute:

### C/C++

`:CocInstall coc-clangd`  # Install clangd-plugin

Open any .c or .cpp file and execute the following command (It is imperative to open a source file, refer: <https://github.com/clangd/coc-clangd/issues/61>)

`:CocCommand clangd.install`  # Install clangd

The above command installs clangd under `~/.config/coc/extensions/coc-clangd-data/install/<version>/clangd_<version>/bin`.

You need to add the above path to the `$PATH` environment variable, preferably in `~/.bashrc` to ensure it is persistent.

Example:
```
export PATH=$PATH:"/home/daljeet/.config/coc/extensions/coc-clangd-data/install/11.0.0/clangd_11.0.0/bin"
```

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

