# IoT Intelligent Irrigation System

This project aims to conserve water and improve crop yields in farming operations using an IoT-based smart irrigation system. The system is designed to optimize water usage by considering soil moisture, temperature, humidity, pressure, and altitude.


-- 3. Total Spending per Customer  
SELECT c.CustomerName, SUM(o.Quantity * b.Price) AS TotalSpending  
FROM Customers c  
JOIN Orders o ON c.CustomerID = o.CustomerID  
JOIN Books b ON o.BookID = b.BookID  
GROUP BY c.CustomerName;  

-- 4. Customer Who Placed the Largest Order  
SELECT c.CustomerName, o.Quantity  
FROM Customers c  
JOIN Orders o ON c.CustomerID = o.CustomerID  
WHERE o.Quantity = (SELECT MAX(Quantity) FROM Orders);  

-- 5. Latest Order Date per Customer  
SELECT c.CustomerName, MAX(o.OrderDate) AS LatestOrderDate  
FROM Customers c  
LEFT JOIN Orders o ON c.CustomerID = o.CustomerID  
GROUP BY c.CustomerName;  
