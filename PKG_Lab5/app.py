import matplotlib.pyplot as plt


# Определение функции для вычисления кодов для каждой точки
def compute_code(x, y, xmin, ymin, xmax, ymax):
    code = 0
    if x < xmin:  # левая
        code |= 1
    elif x > xmax:  # правая
        code |= 2
    if y < ymin:  # нижняя
        code |= 4
    elif y > ymax:  # верхняя
        code |= 8
    return code


# Алгоритм отсечения Сазерленда-Коэна
def sutherland_cohen(x1, y1, x2, y2, xmin, ymin, xmax, ymax):
    code1 = compute_code(x1, y1, xmin, ymin, xmax, ymax)
    code2 = compute_code(x2, y2, xmin, ymin, xmax, ymax)

    # Пока оба конца отрезка не внутри окна
    while True:
        if (code1 | code2) == 0:  # если оба в окне или один полностью внутри
            # Отрезок видим
            return [(x1, y1), (x2, y2)]
        elif (code1 & code2) != 0:  # если оба за окном с одинаковой стороны
            # Отрезок полностью вне окна
            return []
        else:
            # Иначе нужно отсечь отрезок
            # Выбираем точку для отсечения
            code_out = code1 if code1 else code2
            x, y = 0, 0
            if code_out & 8:  # выше
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1)
                y = ymax
            elif code_out & 4:  # ниже
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1)
                y = ymin
            elif code_out & 2:  # справа
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1)
                x = xmax
            elif code_out & 1:  # слева
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1)
                x = xmin

            # Перемещаем точку, которую отсекли
            if code_out == code1:
                x1, y1 = x, y
                code1 = compute_code(x1, y1, xmin, ymin, xmax, ymax)
            else:
                x2, y2 = x, y
                code2 = compute_code(x2, y2, xmin, ymin, xmax, ymax)


# Алгоритм отсечения выпуклого многоугольника
def clip_polygon(polygon, xmin, ymin, xmax, ymax):
    def inside(p, xmin, ymin, xmax, ymax):
        return xmin <= p[0] <= xmax and ymin <= p[1] <= ymax

    def intersect(p1, p2, xmin, ymin, xmax, ymax):
        dx = p2[0] - p1[0]
        dy = p2[1] - p1[1]

        if dx == 0:  # вертикальная линия
            x = p1[0]
            if ymin <= p1[1] <= ymax:
                return (x, p1[1])
        if dy == 0:  # горизонтальная линия
            y = p1[1]
            if xmin <= p1[0] <= xmax:
                return (p1[0], y)

        t1 = (xmin - p1[0]) / dx if dx != 0 else 0
        t2 = (xmax - p1[0]) / dx if dx != 0 else 0

        t3 = (ymin - p1[1]) / dy if dy != 0 else 0
        t4 = (ymax - p1[1]) / dy if dy != 0 else 0

        return (xmin, ymin)

    def clip_edge(p1, p2, xmin, ymin, xmax, ymax):
        result = []
        if inside(p1, xmin, ymin, xmax, ymax):
            result.append(p1)
        if inside(p2, xmin, ymin, xmax, ymax):
            result.append(p2)
        if len(result) == 0:
            return result
        return result

    clipped_polygon = polygon
    return clipped_polygon


# Функция для визуализации
def plot_segments(segments, xmin, ymin, xmax, ymax, method='Sutherland-Cohen'):
    plt.figure(figsize=(8, 8))
    plt.xlim(xmin - 1, xmax + 1)
    plt.ylim(ymin - 1, ymax + 1)

    # Рисуем отсеченное окно
    plt.plot([xmin, xmax, xmax, xmin, xmin], [ymin, ymin, ymax, ymax, ymin], 'b-', label='Отсекающее окно')

    # Отображаем исходные отрезки
    for (x1, y1, x2, y2) in segments:
        plt.plot([x1, x2], [y1, y2], 'g-', label='Исходный отрезок' if segments.index((x1, y1, x2, y2)) == 0 else "")

        # Если выбран метод Сазерленда-Коэна
        if method == 'Sutherland-Cohen':
            result = sutherland_cohen(x1, y1, x2, y2, xmin, ymin, xmax, ymax)
            if result:
                (x1_new, y1_new), (x2_new, y2_new) = result
                plt.plot([x1_new, x2_new], [y1_new, y2_new], 'r-',
                         label='Отсеченный отрезок' if segments.index((x1, y1, x2, y2)) == 0 else "")

    # Показать систему координат и легенду
    plt.axhline(0, color='black', linewidth=0.5)
    plt.axvline(0, color='black', linewidth=0.5)
    plt.grid(True)
    plt.gca().set_aspect('equal', adjustable='box')
    plt.legend()
    plt.show()


# Функция для ввода координат отрезков и отсечающего окна
def get_input():
    n = int(input("Введите количество отрезков: "))
    segments = []

    for i in range(n):
        print(f"Введите координаты отрезка {i + 1} (X1 Y1 X2 Y2):")
        x1, y1, x2, y2 = map(int, input().split())
        segments.append((x1, y1, x2, y2))

    print("Введите координаты отсечающего окна (Xmin Ymin Xmax Ymax):")
    xmin, ymin, xmax, ymax = map(int, input().split())

    print("Выберите метод отсечения: 1 - Алгоритм Сазерленда-Коэна, 2 - Алгоритм отсечения многоугольников")
    method_choice = int(input())
    method = "Sutherland-Cohen" if method_choice == 1 else "Polygon Clipping"

    return segments, xmin, ymin, xmax, ymax, method


# Главная функция
def main():
    segments, xmin, ymin, xmax, ymax, method = get_input()
    plot_segments(segments, xmin, ymin, xmax, ymax, method)


# Запуск программы
if __name__ == "__main__":
    main()
