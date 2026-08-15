import requests
import hashlib
import time

# Blynk token should be provided securely.
TOKEN = "YOUR_BLYNK_AUTH_TOKEN"

# Function to read a value from Blynk virtual pin
def get_value(pin):
    url = f"https://blynk.cloud/external/api/get?token={TOKEN}&{pin}"
    response = requests.get(url)
    return response.text

# Block and Blockchain classes
class Block:
    def __init__(self, data, prev_hash="0"):
        self.timestamp = time.time()
        self.data = data
        self.prev_hash = prev_hash
        self.hash = self.calculate_hash()

    def calculate_hash(self):
        content = str(self.timestamp) + self.data + self.prev_hash
        return hashlib.sha256(content.encode()).hexdigest()


class Blockchain:
    def __init__(self):
        self.chain = [Block("Genesis Block")]

    def add_block(self, data):
        prev = self.chain[-1].hash
        block = Block(data, prev)
        self.chain.append(block)

        print("\n===== NEW BLOCK ADDED =====")
        print("Time:", time.ctime(block.timestamp))
        print("Data:", block.data)
        print("Prev Hash:", block.prev_hash)
        print("Hash:", block.hash)


if __name__ == "__main__":
    bc = Blockchain()

    while True:
        try:
            temp = get_value("v0")   # Temperature
            turb = get_value("v1")   # Turbidity
            ph = get_value("v2")     # pH

            data = f"Temp={temp},Turbidity={turb},pH={ph}"
            print("\nCurrent Sensor Data:", data)

            bc.add_block(data)

            # Wait 10 seconds before next reading
            time.sleep(10)

        except KeyboardInterrupt:
            print("\nStopped by user.")
            break
        except Exception as e:
            print("Error:", e)
            time.sleep(5)
