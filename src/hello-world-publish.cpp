/*
 * Project: Hello World Publish
 * Author: Particle
 * Date: 2025-04-20
 *
 * Description:
 *  This example demonstrates how to register a cloud function that,
 *  when called, publishes a "Hello World" event to the Particle Cloud.
 *  The event will appear in the Particle Console → Logs section.
 *
 * For comprehensive documentation and best practices, visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"

// =====================================================================
// System Configuration
// =====================================================================

// Let Device OS automatically manage the connection to the Particle Cloud.
// This is the most common mode for connected devices.
SYSTEM_MODE(AUTOMATIC);

// Run application and system code concurrently in separate threads.
// This keeps the device responsive to OTA updates and cloud events
// even if your loop() has delays or long-running logic.

#ifndef SYSTEM_VERSION_v620
SYSTEM_THREAD(ENABLED); // System thread defaults to on in 6.2.0 and later and this line is not required
#endif

// Configure logging over USB serial for debugging and visibility.
// Open terminal with: particle serial monitor --follow
SerialLogHandler logHandler(LOG_LEVEL_INFO);

// =====================================================================
// Global Declarations
// =====================================================================

// Function prototype for the cloud function handler.
// Particle.function() expects a specific signature.
int sayHelloHandler(String command);

// =====================================================================
// setup() — runs once when the device starts
// =====================================================================
void setup() {
    // Register a cloud function that can be called from the Console or API.
    //
    // The first argument ("sayHello") is the name that will appear in the
    // Console under the Functions tab.
    // The second argument is the handler function to execute when called.
    Particle.function("sayHello", sayHelloHandler);

    // Log a startup message for visibility.
    Log.info("Setup complete. Cloud function 'sayHello' is ready.");
}

// =====================================================================
// loop() — runs continuously after setup()
// =====================================================================
void loop() {
    // For this example, the main loop does not need to perform any actions.
    // All activity happens when the sayHello function is called from the cloud.

    // It’s good practice to include a small delay to avoid a tight, busy loop.
    delay(100);
}

// =====================================================================
// sayHelloHandler() — Cloud Function
// =====================================================================
// This function is executed whenever the user calls the cloud function
// named "sayHello" from the Console or API.
//
// It demonstrates how to trigger a publish event in response to a cloud
// function call.
//
// Return values:
//   1  → Function executed successfully
//   -1 → Function failed (optional custom logic)
int sayHelloHandler(String command) {
    // Log the received command for debugging (if any data was passed)
    Log.info("Cloud function called with command: %s", command.c_str());

    // Publish an event to the Particle Cloud.
    // The event name is "hello_world" and the data is "Hello from Particle!".
    // The PRIVATE flag ensures the event is not visible to the public event stream.
    Particle.publish("hello_world", "Hello from Particle!");

    // Log for local visibility over serial
    Log.info("Published 'hello_world' event to the cloud.");

    // Return success code
    return 1;
}

