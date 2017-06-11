# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  config.vm.box = "debian/jessie64"
  config.vm.hostname = "tcpip"
  config.vm.network "forwarded_port",
                    guest: 80,
                    host: 8080,
                    protocol: "tcp",
                    auto_correct: true
  # Specified vagrant to not run in sudo mode so rbenv is installed in the right path -> ~/ rather than /root/. 
  config.vm.provision "shell", privileged: false, path: "bootstrap.sh"
  config.vm.provider "virtualbox" do |vb|
    vb.customize ["modifyvm", :id, "--memory", "512"]
  end
end
