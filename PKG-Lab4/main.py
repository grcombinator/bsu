import tkinter as tk
from tkinter import ttk
import math


class RasterAlgorithmsApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Raster Algorithms Visualization")

        self.canvas = tk.Canvas(root, bg="white", width=800, height=600)
        self.canvas.pack(side=tk.TOP, fill=tk.BOTH, expand=True)

        self.scale = tk.Scale(root, from_=1, to=10, orient=tk.HORIZONTAL, label="Scale", command=self.redraw)
        self.scale.pack(side=tk.BOTTOM)

        self.algorithm_var = tk.StringVar(value="DDA")
        self.algorithm_menu = ttk.Combobox(root, textvariable=self.algorithm_var,
                                           values=["Step-by-Step", "DDA", "Bresenham Line", "Bresenham Circle"])
        self.algorithm_menu.pack(side=tk.BOTTOM)
        self.algorithm_menu.bind("<<ComboboxSelected>>", self.redraw)

        self.draw_axes()
        self.redraw()

    def draw_axes(self):
        width = 800
        height = 600
        self.canvas.create_line(width // 2, 0, width // 2, height, fill="black")  # Y-axis
        self.canvas.create_line(0, height // 2, width, height // 2, fill="black")  # X-axis

    def dda(self, x0, y0, x1, y1):
        # DDA algorithm implementation
        dx = x1 - x0
        dy = y1 - y0
        steps = max(abs(dx), abs(dy))

        x_inc = dx / float(steps)
        y_inc = dy / float(steps)

        x = x0
        y = y0
        points = []

        for _ in range(steps):
            points.append((round(x), round(y)))
            x += x_inc
            y += y_inc

        return points

    def bresenham_line(self, x0, y0, x1, y1):
        # Bresenham's line algorithm implementation
        points = []
        dx = x1 - x0
        dy = y1 - y0
        sx = 1 if dx > 0 else -1
        sy = 1 if dy > 0 else -1
        dx = abs(dx)
        dy = abs(dy)

        if dx > dy:
            err = dx / 2.0
            while x0 != x1:
                points.append((x0, y0))
                err -= dy
                if err < 0:
                    y0 += sy
                    err += dx
                x0 += sx
        else:
            err = dy / 2.0
            while y0 != y1:
                points.append((x0, y0))
                err -= dx
                if err < 0:
                    x0 += sx
                    err += dy
                y0 += sy
        points.append((x1, y1))
        return points

    def bresenham_circle(self, xc, yc, r):
        # Bresenham's circle algorithm implementation
        points = []
        x = 0
        y = r
        d = 3 - 2 * r

        while x <= y:
            points.extend([
                (xc + x, yc + y), (xc - x, yc + y),
                (xc + x, yc - y), (xc - x, yc - y),
                (xc + y, yc + x), (xc - y, yc + x),
                (xc + y, yc - x), (xc - y, yc - x)
            ])
            if d < 0:
                d += 4 * x + 6
            else:
                d += 4 * (x - y) + 10
                y -= 1
            x += 1
        return points

    def draw_points(self, points):
        for (x, y) in points:
            if 0 <= x < 800 and 0 <= y < 600:
                self.canvas.create_line(x + 400, 300 - y, x + 400 + 1, 300 - y + 1, fill="blue")

    def redraw(self, event=None):
        self.canvas.delete("all")
        self.draw_axes()
        algorithm = self.algorithm_var.get()

        if algorithm == "DDA":
            points = self.dda(-100, 50, 100, 150)
            self.draw_points(points)
        elif algorithm == "Bresenham Line":
            points = self.bresenham_line(-100, 50, 100, 150)
            self.draw_points(points)
        elif algorithm == "Bresenham Circle":
            points = self.bresenham_circle(0, 0, 100)
            self.draw_points(points)


if __name__ == "__main__":
    root = tk.Tk()
    app = RasterAlgorithmsApp(root)
    root.mainloop()