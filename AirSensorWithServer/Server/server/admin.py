from django.contrib import admin

from .models import Sensor
from .models import Reading

admin.site.register(Sensor)
admin.site.register(Reading)

