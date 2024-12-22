from flask import Flask, render_template, request
import matplotlib.pyplot as plt

app = Flask(__name__)


# Алгоритм Сазерленда-Коэна
def sutherland_cohen(segments, clip_window):
    def compute_code(x, y):
        code = 0
        if x < x_min:  # left
            code |= 1
        elif x > x_max:  # right
            code |= 2
        if y < y_min:  # bottom
            code |= 4
        elif y > y_max:  # top
            code |= 8
        return code

    visible_segments = []
    x_min, y_min, x_max, y_max = clip_window

    for segment in segments:
        x1, y1, x2, y2 = segment
        code1 = compute_code(x1, y1)
        code2 = compute_code(x2, y2)

        while True:
            if (code1 | code2) == 0:  # Both points inside
                visible_segments.append(segment)
                break
            elif (code1 & code2) != 0:  # Both points outside
                break
            else:
                # At least one point is outside
                if code1 != 0:
                    out_code = code1
                else:
                    out_code = code2

                # Find intersection point
                if out_code & 8:  # top
                    x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1)
                    y = y_max
                elif out_code & 4:  # bottom
                    x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1)
                    y = y_min
                elif out_code & 2:  # right
                    y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1)
                    x = x_max
                elif out_code & 1:  # left
                    y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1)
                    x = x_min

                # Replace outside point with intersection point
                if out_code == code1:
                    x1, y1 = x, y
                    code1 = compute_code(x1, y1)
                else:
                    x2, y2 = x, y
                    code2 = compute_code(x2, y2)

                segment = [x1, y1, x2, y2]

    return visible_segments


# Алгоритм отсечения выпуклого многоугольника
def clip_polygon(subject_polygon, clip_polygon):
    def inside(p, edge_start, edge_end):
        return (edge_end[0] - edge_start[0]) * (p[1] - edge_start[1]) > (edge_end[1] - edge_start[1]) * (
                    p[0] - edge_start[0])

    def compute_intersection(p1, p2, edge_start, edge_end):
        A1 = p2[1] - p1[1]
        B1 = p1[0] - p2[0]
        C1 = A1 * p1[0] + B1 * p1[1]

        A2 = edge_end[1] - edge_start[1]
        B2 = edge_start[0] - edge_end[0]
        C2 = A2 * edge_start[0] + B2 * edge_start[1]

        determinant = A1 * B2 - A2 * B1
        if determinant == 0:
            return None  # Параллельные линии

        x = (B2 * C1 - B1 * C2) / determinant
        y = (A1 * C2 - A2 * C1) / determinant
        return (x, y)

    output_polygon = subject_polygon

    for i in range(len(clip_polygon)):
        edge_start = clip_polygon[i]
        edge_end = clip_polygon[(i + 1) % len(clip_polygon)]
        input_polygon = output_polygon
        output_polygon = []

        if not input_polygon:
            break

        S = input_polygon[-1]
        for E in input_polygon:
            if inside(E, edge_start, edge_end):
                if not inside(S, edge_start, edge_end):
                    intersection = compute_intersection(S, E, edge_start, edge_end)
                    if intersection:
                        output_polygon.append(intersection)
                output_polygon.append(E)
            elif inside(S, edge_start, edge_end):
                intersection = compute_intersection(S, E, edge_start, edge_end)
                if intersection:
                    output_polygon.append(intersection)
            S = E

    return output_polygon


# Функция для визуализации
def plot_segments(segments, visible_segments, clip_window):
    plt.figure(figsize=(8, 8))

    # Рисуем отсекающее окно
    x_min, y_min, x_max, y_max = clip_window
    plt.plot([x_min, x_max, x_max, x_min, x_min], [y_min, y_min, y_max, y_max, y_min], color='blue',
             label='Clip Window')

    # Рисуем исходные сегменты
    for segment in segments:
        plt.plot(*zip(*[segment]), color='red', alpha=0.5)

    # Рисуем видимые сегменты
    for segment in visible_segments:
        plt.plot(*zip(*[segment]), color='green', linewidth=2)

    plt.xlim(-10, 10)
    plt.ylim(-10, 10)
    plt.axhline(0, color='black', linewidth=0.5, ls='--')
    plt.axvline(0, color='black', linewidth=0.5, ls='--')
    plt.grid()
    plt.legend()
    plt.savefig('static/output.png')
    plt.close()


@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        data = request.form['data'].strip().splitlines()
        try:
            n = int(data[0])
            segments = [list(map(float, line.split())) for line in data[1:n + 1]]
            clip_window = list(map(float, data[n + 1].split()))
            algorithm = request.form['algorithm']

            if algorithm == 'sutherland':
                visible_segments = sutherland_cohen(segments, clip_window)
            else:  # Алгоритм отсечения выпуклого многоугольника
                # Здесь вы можете задать координаты многоугольника для отсечения
                clip_polygon = [[1, 1], [5, 1], [5, 3], [1, 3]]  # Пример многоугольника
                visible_segments = clip_polygon(segments, clip_polygon)

            plot_segments(segments, visible_segments, clip_window)

            return render_template('index.html', image='output.png')
        except IndexError:
            return render_template('index.html', image=None, error="Ошибка: Проверьте корректность введенных данных.")
        except ValueError:
            return render_template('index.html', image=None, error="Ошибка: Неверный формат данных.")

    return render_template('index.html', image=None)


if __name__ == '__main__':
    app.run(debug=True)