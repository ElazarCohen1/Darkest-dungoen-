from PIL import Image
# Convert the Vestal image to JPG format
input_path_vestal = "image/vestale.webp"
output_path_vestal = "image/vestale.jpg"

# Load and convert to JPG
image_vestal = Image.open(input_path_vestal)
rgb_image_vestal = image_vestal.convert("RGB")  # Convert to RGB for JPG
rgb_image_vestal.save(output_path_vestal, format="JPEG")

output_path_vestal
