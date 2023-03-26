---
title: 'Swift String Substring'
date: 2023-03-23T22:07:21+08:00
author: 'SZH'
tags: ["Swift", "Development", "2023", "2023-03"]
theme: 'dark'
featured: true
draft: true
---

# Swift String Substring

Swift 中对 `String` 类型的 `substring()` 方法都被标记为`不推荐(deprecated)`了，那该如何实现 substring 的功能呢？

![substring is deprecated](../images/swift-string-substring-deprecated.png "XCode 中对String.substring的提示")


根据Xcode的提示可以使用`slicing`的方式：

例: `let str = "0123456789"`

从开始到第一个等于`5`的字符之前的字串：
```swift
if let firstFive = str.firstIndex(of: "5") {
    let substr = str[str.startIndex..<firstFive]
    print("substr = \(substr)") // substr = 01234
}
```

如果包括第一个等于`5`的字符
```swift
let substr = str[str.startIndex...firstFive] // 012345
```
从第一个`5`开始的