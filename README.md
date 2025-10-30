# Blueprint – Beginner – Hello World Publish

**Difficulty:** Beginner  
**Estimated Time:** 15–30 minutes  
**Hardware Needed:** None  
**Particle Features:** `Particle.publish()`, `Particle.function()`, `Console`, `Logs`

---

## Overview
This blueprint demonstrates how to publish a simple “Hello World” event to the Particle Cloud whenever a cloud function is called.  
It’s the ideal first step for understanding how Particle devices communicate with the cloud and respond to Console or API actions.

---

## Tools & Materials
- Any Particle device (Photon 2, Boron, Argon, etc.)  
- USB cable  
- [Particle Workbench](https://docs.particle.io/workbench/) or [Particle CLI](https://docs.particle.io/tutorials/developer-tools/cli/)  
- A Particle account with a claimed device  

---

## Steps
1. **Clone this repository:**
   ```bash
   git clone https://github.com/particle-iot/blueprint-beginner-hello-world-publish.git
   cd blueprint-beginner-hello-world-publish
   ```
2. **Open the project** in Particle Workbench or your preferred editor.  
3. **Flash the firmware** to your device.  
   ```bash
   particle flash <device-name>
   ```
4. **Call the function** from the Particle Console:
   - Go to the *Functions* section.
   - Select the function named `sayHello`.
   - Click *Call* (no arguments required).  
5. **View the result** under *Logs*. You should see an event named `hello_world` with data:  
   ```
   Hello from Particle!
   ```

---

## How It Works
- In `setup()`, the firmware registers a cloud function named `sayHello`.  
- When called from the Console or API, this function executes `sayHelloHandler()`.  
- The handler uses `Particle.publish()` to send a private event called `hello_world` to the cloud.  
- All events are visible in the Console’s *Logs* tab and can also be received by webhooks, integrations, or other devices.

---

## Source Code
The main firmware is located in [`firmware\blueprint-begineer-hello-world-publish\src\hello-world-publish.cpp`](firmware\blueprint-begineer-hello-world-publish\src\hello-world-publish.cpp).  
It’s fully commented to explain how the cloud function and publish mechanism work.

---

### Example Firmware  
(`firmware\blueprint-begineer-hello-world-publish\src\hello-world-publish.cpp`)
```cpp
/*
 * Project: Hello World Publish
 * Author: Your Name
 * Date: YYYY-MM-DD
 *
 * Description:
 *  This example demonstrates how to register a cloud function that,
 *  when called, publishes a "Hello World" event to the Particle Cloud.
 *  The event will appear in the Particle Console → Logs section.
 *
 * For comprehensive documentation and best practices, visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);

int sayHelloHandler(String command);

void setup() {
    Particle.function("sayHello", sayHelloHandler);
    Log.info("Setup complete. Cloud function 'sayHello' is ready.");
}

void loop() {
    delay(100);
}

int sayHelloHandler(String command) {
    Log.info("Cloud function called with command: %s", command.c_str());
    Particle.publish("hello_world", "Hello from Particle!", PRIVATE);
    Log.info("Published 'hello_world' event to the cloud.");
    return 1;
}
```

---

## Expected Output
**Console logs:**
```
Event: hello_world
Data: Hello from Particle!
```

**Serial logs (from `particle serial monitor --follow`):**
```
0000012345 [app] INFO: Cloud function called with command:
0000012346 [app] INFO: Published 'hello_world' event to the cloud.
```

---

## Extensions
- Modify the handler to publish a message containing your device name.  
- Schedule automatic publishes using a software timer.  
- Add a button that triggers the same event locally.
