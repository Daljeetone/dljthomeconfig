# My Space

The repository contains shared config for vim and neovim.

## Clone this repository recursively

```
git clone --recursive git@github.com:Daljeetone/dljthomeconfig.git
```

## Get the latest Vim/NeoVim version

The language server plugin (coc.nvim) needs vim >= `8.1.1719` and neovim >= `0.4.3` to support features like popup and text property.

Currently, Ubuntu 18:04 does not have the required minimum version of Vim/Neovim in its PPA repositories and therefore we need to install it manually. I prefer Neovim over regular Vim so the instructions to install latest Neovim are as follows:

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

## Copy configuration files, download and install utilities (fzf, clangd, nodejs) required by language server

```
./install-tools.sh
```

## Install the Vim plugins

Open Vim and execute the following command, do not worry about the errors that show up when opening Vim.
```
:PluginInstall
```

## Install Language Server Extensions for Vim (On demand)

For each language server you want to use, install the coc plugin for it 
Open Vim and execute:
`:CocInstall coc-clangd`   #C/C++
`:CocInstall coc-go`       #Go
`:CocInstall coc-rls`      #Rust
)

