# IoT Intelligent Irrigation System

This project aims to conserve water and improve crop yields in farming operations using an IoT-based smart irrigation system. The system is designed to optimize water usage by considering soil moisture, temperature, humidity, pressure, and altitude.


-- Task 1: Identify Active Customers
SELECT CustomerID, CustomerName
FROM Customers
WHERE CustomerID IN (SELECT DISTINCT CustomerID FROM Orders);

-- Task 2: Find Books That Have Never Been Ordered
SELECT BookID, Title
FROM Books
WHERE BookID NOT IN (SELECT DISTINCT BookID FROM Orders);

-- Task 3: List Books That Are Out of Stock
SELECT BookID, Title
FROM Books
WHERE Stock = 0;

-- Task 4: Create a View for Order Summary
CREATE VIEW OrderSummary AS
SELECT 
    o.OrderID, 
    c.CustomerName, 
    b.Title AS BookTitle, 
    o.OrderDate, 
    o.Quantity, 
    (o.Quantity * b.Price) AS TotalAmount
FROM Orders o
JOIN Customers c ON o.CustomerID = c.CustomerID
JOIN Books b ON o.BookID = b.BookID;

-- Task 5: Find the Most Expensive Ordered Book
SELECT Title, Price
FROM Books
WHERE Price = (SELECT MAX(Price) FROM Books WHERE BookID IN (SELECT DISTINCT BookID FROM Orders));
