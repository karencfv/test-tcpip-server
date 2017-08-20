# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  config.vm.box = "debian/jessie64"
  config.vm.hostname = "tcpip"
  config.vm.network :private_network, ip: "10.11.12.13"
  config.vm.network "forwarded_port",
                    guest: 80,
                    host: 8080,
                    protocol: "tcp",
                    auto_correct: true
  # Specified vagrant to not run in sudo mode so rbenv is installed in the right path -> ~/ rather than /root/. 
  config.vm.provision "shell", privileged: false, path: "bootstrap.sh"
  config.vm.synced_folder ".", "/var/www", :mount_options => ["dmode=777", "fmode=777"]
  config.vm.provider "virtualbox" do |vb|
    vb.customize ["modifyvm", :id, "--memory", "512"]
  end
end
