mongo-arm
=========

This is a distribution of the MongoDB binaries built for the ARM architecture. Specifically these were build to run on a Raspberry Pi.

Setup Steps:

1. download binaries
	git clone https://github.com/Barryrowe/mongo-arm.git

2. create mongo user
	sudo useradd mongo
	sudo passwd mongo

3. copy mongo binaries to desired install directory
	cp -R binaries/${VERSION} /path/to/install

	example:
		cp -R binaries/2.1.1 /opt/mongo

4. chown mongo binaries to mongo user
	chown -R mongo:mongo /path/to/installed/binaries

5. create directory /data/db
	sudo mkdir /data
	sudo mkdir /data/db

6. chown /data/db to mongo user
	sudo chown mongo:mongo /data/db

7. copy init.d/mongodb to /etc/init.d/mongodb:
	sudo cp init.d/mongodb /etc/init.d/mongodb

8. update /etc/init.d/mongodb to point to your install path from step 3:
	Line 50 will need to be modified to point to the mongos executable from your install path in step 3.
	If you created a user with name other than "mongo" in step 2 you will need to update Line 95 with the user you configured.

9. Update the permissions for the mongodb init.d file:
	sudo chmod 755 /etc/init.d/mongodb

10. Copy the config/mongod.conf file to /etc/mongod.conf:
	sudo cp config/mongod.conf /etc/mongod.conf

11. Register the mongodb service:
	sudo update-rc.d mongodb defaults

12. Start the service:
	sudo service mongodb start


To Manage mongodb you can now:

	#start the service
	sudo service mongodb start

	#check the service status
	service mongodb status

	#stop the service
	sudo service mongodb stop
