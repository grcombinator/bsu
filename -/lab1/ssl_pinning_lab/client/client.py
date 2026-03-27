import requests
import tkinter as tk
from tkinter import ttk, messagebox
import threading
import json

# Вшитый сертификат (скопируй содержимое certA.pem сюда)
PINNED_CERT = """
-----BEGIN CERTIFICATE-----
MIIFCTCCAvGgAwIBAgIUTKMnj9ccK0lt36smif9E+2Ph/sswDQYJKoZIhvcNAQEL
BQAwFDESMBAGA1UEAwwJbG9jYWxob3N0MB4XDTI2MDMyNzE1MTIzOFoXDTI3MDMy
NzE1MTIzOFowFDESMBAGA1UEAwwJbG9jYWxob3N0MIICIjANBgkqhkiG9w0BAQEF
AAOCAg8AMIICCgKCAgEAu09ul7Ls3aC5cfVaelxsvhpRin9drlq2SKumX8MSEk9L
7194CNlp/UR7us43C0ZcT9ahSa4m2Abc9hYVXad6NCxqcTEt8dijcViqP4CPbTDI
GQ46O7Qzuxlb69REht1M1NVBX5cC4jw9n0f9bb1cCKxDKvEDkxX1vgqFReKwaCNa
VQYiICjJwADu8Mfk7kCc6FP6fvnr1iVmodWyCEf3ShmlX6v51+4RwJx6otyCWpkg
hOmvP1V1zAfldVP9iBD7gJ9Q9IhHX7PJXpO4w6OlrrNqczszTpJByi6m+Sf9LWyK
8eEEkcwQ5cQ0l5xdbDgt0c2u8Dfya4VlbnrRH6xMK3s0+gYxkX0ujM3ituixEBY0
HaZgOrWP37RRMcZFIgH9Agz/CiTZ1CE0tpwg/EehxBlmTocLpuK+wlAyMnX68H05
ebczg1e2tGEmyHTUukYzv+7WLZgnZB5JU4F8wC/wmdpd7Ulw1GpPjuct3w7HsIDy
MEA2WKCW4LxZMFzi+GZsRNoVGBy35OVJ8h2XW20dd2yeEt7d0KdQywmhRJwOqCr2
fa5xc/h5541/Kvg40ScH/OUvoZqPZARMv0wTb/+jkkaW4+12Zvz7HAhjiWU1W+pc
ZaTQ9NqWcZGgFsKv0ouh70+jQdUsdnrfgmngaZ+9V6nVLwIFo4uLJeBTuoms2HsC
AwEAAaNTMFEwHQYDVR0OBBYEFLufjzXqGG1Y5HBp7CgnYqWdo62qMB8GA1UdIwQY
MBaAFLufjzXqGG1Y5HBp7CgnYqWdo62qMA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZI
hvcNAQELBQADggIBAJFKmupldE46mzzQ7yZ/azLT6VTT0sm/NMmSrPsv/x6GWZbY
xXFo4Jd9kxbHKlUe2JsTrF8LhGqmTvZD3Kk667ek5FNSUeI12RcCLKRhkp7PkYQ7
PWYBhBKRBoll/dDVxDufOwBT9RmourG9JcXbw1lMvS+TJrGeh9+1YZLLJj4eDP8Q
tr+FMd+xweoK6PXheTCUiuH4UFAuUBlCcPX7D4e0jALDBvNYWeXaVk1JeitCXFda
6MOLH9lw6HaadM6zbAEsa2HbFzAl/Iel1SYHoM0J8dRv+6xRdPNC0K8h3lK7ujKe
gCT34nTyprBt0Uq7OLWWPM7zajOIDdUZng2hi1Ug90LvEyEduOOTjtlel7wgMVXm
bGDRkZuYbDvl5fvr9eT7xfOh/3Ce68H5MShaFGyzexJBTnqLjfIvUS+hk2wN9kAT
6N+8TzHDDRjuSzzilcvZ1l3TqQIKRiTzzcKqv2najwziUWAvCrTAWxSLGYgLK5cR
xOAyf9Au7DbEekMCNGmh8y52rPExbrfEK5EJB8OigP/psLW2rhXpl19XC8HaHkWG
PwsOdc7AUrrgy7GodI0AlLtQNcE+4WT+Cgp4DE6djoBKFfZzxNxG5NCD3QOeXL9u
4lQzZL5QJELBqD5YWrubsh4oVcTYefX6R1te2KpUGjnU/UtDwIY7L/wdoYW5
-----END CERTIFICATE-----

"""


def verify_certificate(cert_bytes):
    """Проверяет, что сертификат сервера совпадает с вшитым"""
    return cert_bytes.strip() == PINNED_CERT.strip()


def fetch_stocks():
    url = "https://localhost:4443/stocks-data.json"
    try:
        # Отключаем стандартную проверку SSL, делаем свою
        response = requests.get(url, verify=False)

        # Получаем сертификат сервера
        cert = response.raw.connection.sock.getpeercert(binary_form=True)
        if not verify_certificate(cert):
            raise Exception("Сертификат сервера не совпадает с вшитым! SSL Pinning error.")

        data = response.json()
        return data
    except Exception as e:
        raise Exception(f"Ошибка: {e}")


class App:
    def __init__(self, root):
        self.root = root
        self.root.title("Мониторинг акций")
        self.root.geometry("500x300")

        self.frame = ttk.Frame(root, padding="10")
        self.frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))

        self.label = ttk.Label(self.frame, text="Нажмите кнопку для загрузки данных", font=("Arial", 14))
        self.label.grid(row=0, column=0, pady=10)

        self.btn = ttk.Button(self.frame, text="Загрузить данные", command=self.load_data)
        self.btn.grid(row=1, column=0, pady=10)

        self.tree = ttk.Treeview(self.frame, columns=("name", "price"), show="headings", height=10)
        self.tree.heading("name", text="Компания")
        self.tree.heading("price", text="Цена ($)")
        self.tree.grid(row=2, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))

    def load_data(self):
        self.btn.config(state=tk.DISABLED)
        self.label.config(text="Загрузка...")

        def task():
            try:
                data = fetch_stocks()
                self.root.after(0, self.update_ui, data)
            except Exception as e:
                self.root.after(0, self.show_error, str(e))

        threading.Thread(target=task, daemon=True).start()

    def update_ui(self, data):
        for row in self.tree.get_children():
            self.tree.delete(row)

        for symbol, info in data.items():
            self.tree.insert("", tk.END, values=(info["name"], info["price"]))

        self.label.config(text="Данные загружены")
        self.btn.config(state=tk.NORMAL)

    def show_error(self, msg):
        messagebox.showerror("Ошибка", msg)
        self.label.config(text="Ошибка загрузки")
        self.btn.config(state=tk.NORMAL)


if __name__ == "__main__":
    root = tk.Tk()
    app = App(root)
    root.mainloop()