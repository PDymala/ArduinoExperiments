# AirSensorWithServer

This project had 3 parts:

- Establishing a private database, in my case, on a private VM
- Making a serverless (Cloud Run) Python, Django API (REST API) which worked as a gateway to put date into DB
- Arduino (rev2 wifi) which had a temperature and humidity sensor that sent data to database via server(less) app. Additionally 2 LEDs to know if the data is being sent properly.


