#!/usr/bin/env bash

if ! [ -L /var/www  ]; then
  sudo rm -rf /var/www
  sudo ln -fs /vagrant /var/www
fi

sudo apt-get -y update

# Install necessary dependencies for rbenv and ruby
sudo apt-get -y install autoconf bison git-core curl zlib1g-dev build-essential libssl-dev libreadline-dev libncurses5-dev libyaml-dev libsqlite3-dev sqlite3 libxml2-dev libxslt1-dev libcurl4-openssl-dev python-software-properties libffi-dev libgdbm3 libgdbm-dev vim<<EOF
Y
EOF

git clone https://github.com/rbenv/rbenv.git ~/.rbenv

echo 'export PATH="$HOME/.rbenv/bin:$PATH"' >> ~/.bashrc
echo 'eval "$(rbenv init -)"' >> ~/.bashrc

source ~/.bashrc

git clone https://github.com/rbenv/ruby-build.git ~/.rbenv/plugins/ruby-build

sudo -H -u vagrant bash -i -c 'rbenv install 2.4.1'
sudo -H -u vagrant bash -i -c 'rbenv global 2.4.1'
