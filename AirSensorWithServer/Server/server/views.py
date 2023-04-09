from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt

from server.models import Reading, Sensor


@csrf_exempt
def index(request):
    if request.method == 'GET':
        return HttpResponse(False)
    elif request.method == 'POST':
        print(request)
        temperature = request.POST.get("temperature")
        humidity = request.POST.get("humidity")
        heatIndex = request.POST.get("heatIndex")
        sensorId = request.POST.get("sensorId")
        print(sensorId, temperature, humidity, heatIndex)
        currentSensor = Sensor.objects.get(pk=sensorId)

        new_reading = Reading.objects.create(
            temperature=temperature,
            humidity=humidity,
            heatIndex=heatIndex,
            sensor=currentSensor
        )

        return HttpResponse(True)

    else:
        return HttpResponse(False)
