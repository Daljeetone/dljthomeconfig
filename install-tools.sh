#!/bin/bash

CONFIG_SRC_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

echo -e "\e[32mInstalling configuration from:$CONFIG_SRC_DIR\e[0m"

if [ -z "$XDG_CONFIG_HOME" ]; then
    USER_CONFIG_DIR="$HOME/.config"
else
    USER_CONFIG_DIR="$XDG_CONFIG_HOME"
fi

cp -r "$CONFIG_SRC_DIR/.config/nvim" "$USER_CONFIG_DIR/"
NEOVIM_CONFIG_DIR=$USER_CONFIG_DIR/nvim
echo "Neovim config dir located at:$NEOVIM_CONFIG_DIR"

cp -r "$CONFIG_SRC_DIR/.vim" "$HOME/"
cp -r "$CONFIG_SRC_DIR/.vimrc" "$HOME/"
cp -r "$CONFIG_SRC_DIR/.coc.vim" "$HOME/"
cp -r "$CONFIG_SRC_DIR/.fzf" "$HOME/"

pushd ~/.fzf
./install
popd

sudo apt install silversearcher-ag

sudo apt install curl

#Install Node.js, needed to run coc.nvim
curl -sL install-node.now.sh/lts | sudo bash

#Install Yarn Package Manager needed to build coc.nvim
sudo npm install -g yarn

CONFIG_SRC_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

pushd "$HOME/.vim/bundle/coc.nvim"

yarn install --frozen-lockfile

popd
echo "set completion-ignore-case On" > "$HOME/.inputrc"

echo ""
echo -e "\e[32m"You should open Vim and do ":PluginInstall" "\e[0m"
echo "Refer to README for further instructions after doing :PluginInstall"
