$script = <<SCRIPT
sudo apt-get install -y build-essential
curl -sL https://deb.nodesource.com/setup_0.12 | sudo bash -
# curl -sL https://deb.nodesource.com/setup_0.10 | sudo bash -
# curl -sL https://deb.nodesource.com/setup_iojs_1.x | sudo bash -
 sudo apt-get install -y nodejs
# sudo apt-get install -y iojs
sudo npm install -g node-gyp
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
