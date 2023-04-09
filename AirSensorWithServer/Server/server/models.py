from django.db import models

# Create your models here.
class Sensor(models.Model):
    name = models.CharField('name', max_length=1000)
    location = models.CharField('location',max_length=1000)

class Reading(models.Model):
    creation_date = models.DateTimeField('creation_date', auto_now_add=True)
    temperature = models.FloatField('temperature')
    humidity = models.FloatField('humidity')
    heatIndex = models.FloatField('heatIndex')
    sensor = models.ForeignKey(Sensor, on_delete=models.CASCADE, null=False)

    def __str__(self):
        return str(self.pk)