*This project is a part of The [SOOMLA](http://project.soom.la) Framework which is a series of open source initiatives with a joint goal to help mobile game developers do more together. SOOMLA encourages better game designing, economy modeling and faster development.*

soomla-android-core
===============

When using the SOOMLA framework, you always start by initializing the core module:
```java
Soomla.initialize("[YOUR SOOMLA SECRET HERE]");
```

This sets up the local on-device database used by SOOMLA.  The secret is used for encrypting the data, make sure to choose a good one.

This core library holds common features and utilities used by all other modules of the SOOMLA framework.
It includes:
* An encrypted key-value storage (SQLite based) for persisting data locally on devices.
* Utilities for `String` and `JSONObject` manipulation.
* Utilities for Logging and encryption.
* An event bus (using Square's otto) for publish-subscribe events.
* Reward domain objects and events - used to grant your users rewards.

SOOMLA modules internally use these features, though we encourage you to use them for your own needs as well.  For example, use our key-value storage for custom game data for usage across game sessions.


Our way of saying "Thanks !"
---

Other open-source projects that we use:

* [FBEncryptor](https://github.com/dev5tec/FBEncryptor)
* [Otto](http://square.github.io/otto/) - by Square

Contribution
---

We want you!

Fork -> Clone -> Implement —> Insert Comments -> Test -> Pull-Request. We have great RESPECT for contributors.

Code Documentation
---

We follow strict code documentation conventions. If you would like to contribute please read our [Documentation Guidelines](https://github.com/soomla/android-store/blob/master/documentation.md) and follow them. Clear, consistent  comments will make our code easy to understand.

SOOMLA, Elsewhere ...
---

+ [Framework Page](http://project.soom.la/)
+ [On Facebook](https://www.facebook.com/pages/The-SOOMLA-Project/389643294427376).
+ [On AngelList](https://angel.co/the-soomla-project)

License
---
Apache License. Copyright (c) 2012-2014 SOOMLA. http://project.soom.la
+ http://opensource.org/licenses/Apache-2.0
