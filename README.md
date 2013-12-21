MongoDB for ARM
=========

This is a distribution of the MongoDB binaries built for the ARM architecture. Specifically these were built to run on a Raspberry Pi.

Setup Steps:
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

7. Copy **config/mongodb** to the init.d location

	```bash
	sudo cp init.d/mongodb /etc/init.d/mongodb
	```

8. Update /etc/init.d/mongodb to point to your install path from step 3
	
	A. **Line 50** will need to be modified to point to the mongos executable from your install path in step 3.
	
	B. If you created a user with name other than "mongo" in step 2 you will need to update **Line 95** with the user you configured.

9. Update the permissions for the mongodb init.d file so it can be executed

	```bash
	sudo chmod 755 /etc/init.d/mongodb
	```

10. Copy the **config/mongod.conf** file to /etc/mongod.conf

	```bash
	sudo cp config/mongod.conf /etc/mongod.conf
	```

11. Register the mongodb service

	```bash
	sudo update-rc.d mongodb defaults
	```

12. Startup the service

	```bash
	sudo service mongodb start
	```

Managing MongoDB After Install
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
