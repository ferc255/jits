# -*- mode: ruby -*-
# vi: set ft=ruby :

# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = "ubuntu/bionic64"
  config.vm.define "jits" do |define|
  end
  config.vm.hostname = "jits-host"

  config.vm.synced_folder ".", "/vagrant", type: "nfs"
  
  config.vm.network "forwarded_port", guest: 8888, host: 8845
  config.vm.network "private_network", type: "dhcp"


  config.vm.provider "virtualbox" do |vb|
    vb.name = "vb_jits"
    vb.customize ["modifyvm", :id, "--cpus", "2"]
    vb.customize ["modifyvm", :id, "--memory", "4096"]
    vb.customize ["modifyvm", :id, "--natdnshostresolver1", "on"]
  end
end
