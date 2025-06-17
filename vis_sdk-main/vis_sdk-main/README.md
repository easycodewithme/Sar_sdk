# 🧠 sil-sdk

**`sil-sdk`** is a lightweight Python SDK that enables communication with a modular vision inference server. It supports multiple AI vision modules such as object detection, pose estimation, OCR, and vision-language reasoning.

---

## 📦 Installation

```bash
pip install sil-sdk
```

> Requires: Python 3.7+

---

## 🚀 Basic Examples

### 🖼️ Single-frame Module (e.g., `llava`)

```python
from sil_sdk.modules.vis import VISModule
import base64, cv2, numpy as np

vis = VISModule(server_uri="ws://localhost:50004", start_server=False)
vis.load("llava")
vis.run("llava", prompt="count the number of persons")

result = vis.get_result("llava")
if result:
    print("LLaVA Result:", result["result"])
    image_b64 = result.get("image")
    if image_b64:
        img_data = base64.b64decode(image_b64)
        np_arr = np.frombuffer(img_data, np.uint8)
        frame = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)
        cv2.imshow("LLaVA Output", frame)
        cv2.waitKey(0)
```

---

### 📹 Live Module (e.g., `yolo_seg_track`)

```python
import time, base64, cv2, numpy as np
from sil_sdk.modules.vis import VISModule

vis = VISModule(server_uri="ws://localhost:50004")
vis.load("yolo_seg_track")
vis.run("yolo_seg_track")

while True:
    result = vis.get_result("yolo_seg_track")
    if result:
        print(result["result"])
        image_b64 = result.get("image")
        if image_b64:
            img_data = base64.b64decode(image_b64)
            np_arr = np.frombuffer(img_data, np.uint8)
            frame = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)
            cv2.imshow("YOLO Output", frame)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

vis.stop_module("yolo_seg_track")
cv2.destroyAllWindows()
vis.close()
```

---

## 🧠 Supported Modules

| Module Name        | Description                      |
|--------------------|----------------------------------|
| `obj_detection`    | YOLO object detection            |
| `gdino`            | Grounding DINO (zero-shot)       |
| `owl_vit`          | OWL-ViT zero-shot detector       |
| `hum_pose`         | Human pose estimation            |
| `ocr`              | PaddleOCR (text detection)       |
| `yolo_seg_track`   | YOLO segmentation and tracking   |
| `hand_pose`        | Hand pose estimation             |
| `midas_depth`      | MiDaS depth estimation           |
| `llava`            | LLaVA vision-language reasoning  |

---

## 🛠 SDK API

### `VISModule(server_uri="ws://...", start_server=False)`
Initializes the connection to the WebSocket server.

---

### `load(module or list)`
Loads one or more modules for inference.

```python
vis.load("llava")
vis.load(["llava", "gdino"])
```

---

### `run(module_name, prompt=None)`
Runs the specified module. Pass an optional `prompt` for modules like `llava`.

---

### `get_result(module_name)`
Fetches the result (output, image, bbox, text, etc.) from the specified module.

---

### `stop_module(module_name)`
Stops the specified module if it's running.

---

### `close()`
Closes the WebSocket connection cleanly.

---

## 📝 License

Proprietary - Sastra Innovation Labs

This software is the property of Sastra Innovation Labs. Unauthorized copying, distribution, modification, or use is prohibited.


