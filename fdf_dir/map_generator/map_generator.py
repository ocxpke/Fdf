import os
import sys
import cv2
import numpy as np
import argparse
from PIL import Image

# Comprobar si imporar os no da problemas de seguridad
# Lo mismo con sys
input_path = sys.argv[1]

base_name = os.path.splitext(os.path.basename(input_path))[0]

bw_image_path = f"{base_name}_bw.png"
pixel_image_path = f"{base_name}_pixelada.png"
fdf_output_path = f"{base_name}.fdf"

# 1. Argumentos desde la línea de comandos
parser = argparse.ArgumentParser(description="Convierte una imagen a .fdf para FdF de 42.")
parser.add_argument("image_path", type=str, help="Ruta a la imagen de entrada.")
args = parser.parse_args()

# 2. Leer imagen original
input_path = args.image_path
img = cv2.imread(input_path)
if img is None:
    raise FileNotFoundError(f"No se pudo cargar la imagen en {input_path}")

# 3. Convertir a blanco y negro
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
bw_output_path = bw_image_path
cv2.imwrite(bw_output_path, gray)  # Guardamos la versión en blanco y negro

# 4. Redimensionar a 100x100 (pixelado)
pixelated = cv2.resize(gray, (100, 100), interpolation=cv2.INTER_AREA)
pixel_output_path = pixel_image_path
cv2.imwrite(pixel_output_path, pixelated)

# 5. Mapear de escala de grises (0-255) al rango 0-16
mapped = (pixelated / 255 * 16).astype(int)

# 6. Crear archivo FDF
with open(fdf_output_path, "w") as f:
    for row in mapped:
        line = " ".join(str(z) for z in row)
        f.write(line + "\n")

print(f"[✔] Imagen en blanco y negro guardada en: {bw_output_path}")
print(f"[✔] Imagen pixelada guardada en: {pixel_output_path}")
print(f"[✔] Archivo .fdf generado en: {fdf_output_path}")
