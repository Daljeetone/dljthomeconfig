#!/bin/bash

sudo apt install curl

#Install Node.js, needed to run coc.nvim
curl -sL install-node.now.sh/lts | sudo bash

#Install Yarn Package Manager needed to build coc.nvim
sudo npm install -g yarn

CONFIG_SRC_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

pushd "$HOME/.vim/bundle/coc.nvim"

yarn install --frozen-lockfile

popd
