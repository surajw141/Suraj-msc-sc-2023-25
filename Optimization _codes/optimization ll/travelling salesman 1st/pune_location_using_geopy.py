from geopy.geocoders import Nominatim
geolocator = Nominatim(user_agent="Suraw141_app")

pt = geolocator.geocode("Pune, India").point
print(pt[0],pt[1])

