import cv2
import numpy as np
from flask import Flask, render_template, request, send_file
from io import BytesIO
from PIL import Image

# Инициализация Flask-приложения
app = Flask(__name__)


# Функции для обработки изображений

# 1. Обнаружение точек (например, с помощью детектора Хаара или Детектора углов Ши-Томаси)
def detect_points(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    corners = cv2.goodFeaturesToTrack(gray, 100, 0.01, 10)
    corners = np.int0(corners)
    for i in corners:
        x, y = i.ravel()
        cv2.circle(image, (x, y), 3, 255, -1)
    return image


# 2. Обнаружение линий (использование преобразования Хафа)
def detect_lines(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    edges = cv2.Canny(gray, 50, 150, apertureSize=3)
    lines = cv2.HoughLines(edges, 1, np.pi / 180, 200)
    if lines is not None:
        for rho, theta in lines[:, 0]:
            a = np.cos(theta)
            b = np.sin(theta)
            x0 = a * rho
            y0 = b * rho
            x1 = int(x0 + 1000 * (-b))
            y1 = int(y0 + 1000 * (a))
            x2 = int(x0 - 1000 * (-b))
            y2 = int(y0 - 1000 * (a))
            cv2.line(image, (x1, y1), (x2, y2), (0, 0, 255), 2)
    return image


# 3. Обнаружение перепадов яркости (например, с помощью оператора Собеля)
def detect_gradients(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    grad_x = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize=3)
    grad_y = cv2.Sobel(gray, cv2.CV_64F, 0, 1, ksize=3)
    grad_mag = cv2.magnitude(grad_x, grad_y)
    grad_mag = np.uint8(np.absolute(grad_mag))
    return cv2.applyColorMap(grad_mag, cv2.COLORMAP_JET)


# 4. Глобальная пороговая обработка (Метод Оцу)
def global_thresholding_otsu(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    _, thresh = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
    return thresh


# 5. Глобальная пороговая обработка (Метод с фиксированным порогом)
def global_thresholding_fixed(image, threshold_value=127):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    _, thresh = cv2.threshold(gray, threshold_value, 255, cv2.THRESH_BINARY)
    return thresh


# 6. Адаптивная пороговая обработка
def adaptive_thresholding(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    thresh = cv2.adaptiveThreshold(gray, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 11, 2)
    return thresh


# Основная страница
@app.route('/')
def index():
    return render_template('index.html')


# Обработка загруженного изображения
@app.route('/process', methods=['POST'])
def process_image():
    if 'file' not in request.files:
        return "No file part"

    file = request.files['file']
    if file.filename == '':
        return 'No selected file'

    # Чтение и обработка изображения
    image = np.array(Image.open(file).convert('RGB'))

    # Выполнение различных методов обработки
    if request.form['method'] == 'detect_points':
        processed_image = detect_points(image)
    elif request.form['method'] == 'detect_lines':
        processed_image = detect_lines(image)
    elif request.form['method'] == 'detect_gradients':
        processed_image = detect_gradients(image)
    elif request.form['method'] == 'global_otsu':
        processed_image = global_thresholding_otsu(image)
    elif request.form['method'] == 'global_fixed':
        processed_image = global_thresholding_fixed(image)
    elif request.form['method'] == 'adaptive':
        processed_image = adaptive_thresholding(image)

    # Преобразуем результат в изображение для отправки пользователю
    pil_img = Image.fromarray(processed_image)
    img_byte_arr = BytesIO()
    pil_img.save(img_byte_arr, format='PNG')
    img_byte_arr.seek(0)

    return send_file(img_byte_arr, mimetype='image/png')


if __name__ == '__main__':
    app.run(debug=True)
