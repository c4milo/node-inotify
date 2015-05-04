$script = <<SCRIPT
sudo apt-get update -y
apt-get install -y build-essential
curl -sL https://deb.nodesource.com/setup_0.12 | sudo bash -
sudo apt-get install -y nodejs
SCRIPT

Vagrant.configure("2") do |config|
	config.vm.box = "ubuntu/trusty64"
	config.vm.box_check_update = false

	config.vm.hostname = "inotify.local"

	config.vm.provider "virtualbox" do |vb|
		vb.gui = false
		vb.memory = 1024
		vb.cpus = 1
	end

	config.vm.provision "shell", inline: $script
end
