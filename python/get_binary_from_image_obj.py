def extract_binary_data_from_image_object(image: Image.Image, format: str = "PNG") -> bytes:
  byte_buffer = io.BytesIO
  image.save(byte_buffer, format=format)
  return byte_buffer.getvalue()
