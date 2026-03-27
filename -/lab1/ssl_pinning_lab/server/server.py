from http.server import HTTPServer, BaseHTTPRequestHandler
import ssl
import json
import random

# Данные акций (реальные символы, но цены генерируем)
stocks = {
    "AAPL": {"name": "Apple Inc.", "price": 175.00},
    "GOOGL": {"name": "Alphabet Inc.", "price": 140.00},
    "MSFT": {"name": "Microsoft Corp.", "price": 420.00},
    "AMZN": {"name": "Amazon.com Inc.", "price": 185.00},
}


class StockHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == "/stocks-data.json":
            self.send_response(200)
            self.send_header("Content-type", "application/json")
            self.end_headers()

            # Обновляем цены случайными изменениями
            for stock in stocks.values():
                stock["price"] = round(stock["price"] + random.uniform(-5, 5), 2)

            response = json.dumps(stocks, indent=2)
            self.wfile.write(response.encode())
        else:
            self.send_response(404)
            self.end_headers()


def run_server(cert_file, key_file, port=4443):
    server = HTTPServer(("localhost", port), StockHandler)
    ssl_context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
    ssl_context.load_cert_chain(cert_file, key_file)
    server.socket = ssl_context.wrap_socket(server.socket, server_side=True)
    print(f"Сервер запущен на https://localhost:{port}")
    print(f"Используется сертификат: {cert_file}")
    server.serve_forever()


if __name__ == "__main__":
    import sys

    if len(sys.argv) != 2:
        print("Использование: python server.py [A|B]")
        sys.exit(1)

    choice = sys.argv[1].upper()
    if choice == "A":
        run_server("certA.pem", "keyA.pem")
    elif choice == "B":
        run_server("certB.pem", "keyB.pem")
    else:
        print("Аргумент должен быть A или B")