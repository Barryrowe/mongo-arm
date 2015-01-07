**NOTE January 7th, 2015:** I have not been actively working on this project, and realize the binaries are quite old (v2.1.1). I started this as a proof of concept, and have stopped work on the project it supported. The MongoDB team is working on ARM support, but it relies on several large core-unit refactors or re-writes. You can view the status on their JIRA ticket here: [MongoDB Support for ARM JIRA Ticket](https://jira.mongodb.org/browse/SERVER-1811)

MongoDB for ARM
=========

This is a distribution of the MongoDB binaries built for the ARM architecture. Specifically these were built to run MongoDB on a Raspberry Pi. This was tested and built using a [Model B Pi](http://www.newark.com/raspberry-pi/raspbrry-modb-512m/model-b-assembled-board-only/dp/43W5302) running [Raspbian Wheezy 3.6.11+](http://www.raspbian.org/RaspbianImages) Available for Download [Here](http://www.raspberrypi.org/downloads) 

I can only take credit for compiling these instructions in one place, and providing a compiled set of binaries. These binaries and instructions are based on information from the following links:

[Compiling MongoDB](http://c-mobberley.com/wordpress/index.php/2013/10/14/raspberry-pi-mongodb-installation-the-working-guide/)

[Building MongoDB on the Raspberry Pi - mongopi](http://mongopi.wordpress.com/2012/11/25/installation/)

[Setting Up MongoDB as A Service](http://stackoverflow.com/questions/17901627/setting-up-mongodb-raspberry-pi)

Issues
---------
- The mongo shell causes Segmentation Fault errors when running "show dbs;" and sometimes when querying collections. 
	**NOTE:** the pymongo driver is tested and works well against this installation process. It appears only the shell has this issue.

Installation Steps:
---------

1. Download binaries

	```bash
	#Clone this repository
	git clone https://github.com/Barryrowe/mongo-arm.git
	```

2. Create the **mongo** user

	```bash
	sudo useradd mongo
	sudo passwd mongo
	```

3. Copy the mongo binaries to the desired install location

	```bash
	#example:
	cp -R binaries/2.1.1 /opt/mongo
	```

4. Change the ownership of the installed mongo binaries so they are owned by the **mongo** user

	```bash	
	chown -R mongo:mongo /path/to/installed/binaries
	```

5. Creat the **/data/db** directory for MongoDB's data storage

	```bash	
	sudo mkdir /data
	sudo mkdir /data/db
	```

6. Change the ownership of the **/data/db** directory so it is owned by the **mongo** user

	```bash
	sudo chown mongo:mongo /data/db
	```

Set As Service Steps (Debian)
---------

1. Copy **config/mongodb** to the init.d location

	```bash
	sudo cp config/mongodb /etc/init.d/mongodb
	```

2. Update /etc/init.d/mongodb to point to your install path from step 3
	
	A. **Line 50** will need to be modified to point to the mongos executable from your install path in step 3.
	
	B. If you created a user with name other than "mongo" in step 2 you will need to update **Line 95** with the user you configured.

3. Update the permissions for the mongodb init.d file so it can be executed

	```bash
	sudo chmod 755 /etc/init.d/mongodb
	```

4. Copy the **config/mongod.conf** file to /etc/mongod.conf

	```bash
	sudo cp config/mongod.conf /etc/mongod.conf
	```

5. Register the mongodb service

	```bash
	sudo update-rc.d mongodb defaults
	```

6. Startup the service

	```bash
	sudo service mongodb start
	```

Managing MongoDB After Install and Setting as Service
---------

Once installed and configured, you can use these commands to manage the mongodb service you've setup.

```bash
#start the service
sudo service mongodb start

#check the service status
service mongodb status

#stop the service
sudo service mongodb stop
```

If your mongodb service won't start you might just get output like this:

```bash
....] Starting database: mongod/etc/init.d/mongodb: 131: ulimit: Illegal option -u
numactl: 
daemuser: mongo
pidfile: /var/run/mongod.pid
daem: /opt/mongo/bin/mongod
daemopts: -- --config /etc/mongod.conf
. failed
```
***NOTE:*** In this case, make sure to check the ***/data/db/*** directory for a file ***mongod.lock***. If mongodb isn't stopped cleanly, the mongod process can leave this lock file in place preventing the service from properly starting. Usually you can just remove the file and mongodb will start normally

```bash
#remove mongod.lock file after unclean shutdown
sudo rm /data/db/mongod.lock
```

