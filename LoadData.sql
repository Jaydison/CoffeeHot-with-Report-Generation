USE coffee_shop;

START TRANSACTION;

INSERT INTO ADMINS
    (AdminID, Username, PasswordHash, AdminName, AdminStatus, CreatedAt)
VALUES
    (1, 'admin01', 'root', 'System Administrator', 'Active', '2026-07-20 09:30:00')
ON DUPLICATE KEY UPDATE
    PasswordHash = VALUES(PasswordHash),
    AdminName = VALUES(AdminName),
    AdminStatus = VALUES(AdminStatus);


INSERT INTO CATEGORIES
    (CategoryID, CategoryName, CategoryDescription, CategoryStatus)
VALUES
    (1, 'Coffee', 'Espresso and coffee-based beverages', 'Active'),
    (2, 'Non-Coffee', 'Milk, chocolate, tea, and other non-coffee beverages', 'Active'),
    (3, 'Juice', 'Fruit juices and refreshing fruit beverages', 'Active')
ON DUPLICATE KEY UPDATE
    CategoryDescription = VALUES(CategoryDescription),
    CategoryStatus = VALUES(CategoryStatus);


INSERT INTO SIZE_OPTIONS
    (SizeID, SizeName, AdditionalPrice, SizeStatus)
VALUES
    (1, 'Small', 0.00, 'Active'),
    (2, 'Medium', 1.00, 'Active'),
    (3, 'Large', 2.00, 'Active')
ON DUPLICATE KEY UPDATE
    AdditionalPrice = VALUES(AdditionalPrice),
    SizeStatus = VALUES(SizeStatus);


INSERT INTO ADD_ONS
    (AddOnID, AddOnName, AddOnPrice, AddOnStatus)
VALUES
    (1, 'Extra Shot', 1.50, 'Active'),
    (2, 'Whipped Cream', 1.00, 'Active'),
    (3, 'Caramel Syrup', 0.75, 'Active'),
    (4, 'Vanilla Syrup', 0.75, 'Active'),
    (5, 'Chocolate Syrup', 0.75, 'Active'),
    (6, 'Oat Milk', 1.25, 'Active')
ON DUPLICATE KEY UPDATE
    AddOnPrice = VALUES(AddOnPrice),
    AddOnStatus = VALUES(AddOnStatus);


INSERT INTO PAYMENT_METHODS
    (PaymentMethodID, PaymentMethodName, PaymentStatus)
VALUES
    (1, 'Cash', 'Active'),
    (2, 'Credit Card', 'Active'),
    (3, 'E-Wallet', 'Active')
ON DUPLICATE KEY UPDATE
    PaymentStatus = VALUES(PaymentStatus);


INSERT INTO BEVERAGES
    (BeverageID, CategoryID, BeverageName, BeverageDescription, BasePrice, BeverageStatus)
VALUES
    (101, 1, 'Espresso', 'Concentrated coffee shot', 3.00, 'Available'),
    (102, 1, 'Americano', 'Espresso with hot water', 3.50, 'Available'),
    (103, 1, 'Cappuccino', 'Espresso with steamed milk and foam', 4.50, 'Available'),
    (104, 1, 'Cafe Latte', 'Espresso with steamed milk', 4.75, 'Available'),
    (105, 1, 'Caramel Macchiato', 'Espresso, milk, vanilla, and caramel', 5.50, 'Available'),
    (106, 1, 'Cafe Mocha', 'Espresso with chocolate and steamed milk', 5.25, 'Available'),

    (201, 2, 'Hot Chocolate', 'Chocolate drink with steamed milk', 4.00, 'Available'),
    (202, 2, 'Matcha Latte', 'Matcha green tea with milk', 4.75, 'Available'),
    (203, 2, 'Milk Tea', 'Black tea blended with milk', 4.25, 'Available'),
    (204, 2, 'Vanilla Milk', 'Milk flavored with vanilla', 3.75, 'Available'),

    (301, 3, 'Orange Juice', 'Refreshing orange juice', 3.50, 'Available'),
    (302, 3, 'Apple Juice', 'Refreshing apple juice', 3.50, 'Available'),
    (303, 3, 'Mango Juice', 'Sweet mango fruit beverage', 4.00, 'Available'),
    (304, 3, 'Watermelon Juice', 'Fresh watermelon fruit beverage', 4.00, 'Available')
ON DUPLICATE KEY UPDATE
    CategoryID = VALUES(CategoryID),
    BeverageDescription = VALUES(BeverageDescription),
    BasePrice = VALUES(BasePrice),
    BeverageStatus = VALUES(BeverageStatus);


INSERT INTO STOCK
    (StockID, BeverageID, QuantityAvailable, LowStockLevel, LastUpdated, UpdatedBy)
VALUES
    (1, 101, 50, 5, '2026-08-05 09:00:00', 1),
    (2, 102, 50, 5, '2026-08-05 09:00:00', 1),
    (3, 103, 40, 5, '2026-08-05 09:00:00', 1),
    (4, 104, 40, 5, '2026-08-05 09:00:00', 1),
    (5, 105, 30, 5, '2026-08-05 09:00:00', 1),
    (6, 106, 30, 5, '2026-08-05 09:00:00', 1),
    (7, 201, 35, 5, '2026-08-05 09:00:00', 1),
    (8, 202, 30, 5, '2026-08-05 09:00:00', 1),
    (9, 203, 35, 5, '2026-08-05 09:00:00', 1),
    (10, 204, 25, 5, '2026-08-05 09:00:00', 1),
    (11, 301, 30, 5, '2026-08-05 09:00:00', 1),
    (12, 302, 30, 5, '2026-08-05 09:00:00', 1),
    (13, 303, 25, 5, '2026-08-05 09:00:00', 1),
    (14, 304, 25, 5, '2026-08-05 09:00:00', 1)
ON DUPLICATE KEY UPDATE
    QuantityAvailable = VALUES(QuantityAvailable),
    LowStockLevel = VALUES(LowStockLevel),
    LastUpdated = VALUES(LastUpdated),
    UpdatedBy = VALUES(UpdatedBy);


INSERT INTO SALES_TRANSACTIONS
    (TransactionID, PaymentMethodID, TransactionTimestamp, Subtotal, TotalAddOnAmount, GrandTotal, TransactionStatus)
VALUES
    (10001, 3, '2026-08-05 10:25:30', 5.50, 1.50, 7.00, 'Completed'),
    (10002, 1, '2026-08-05 11:10:00', 9.00, 1.00, 10.00, 'Completed')
ON DUPLICATE KEY UPDATE
    PaymentMethodID = VALUES(PaymentMethodID),
    TransactionTimestamp = VALUES(TransactionTimestamp),
    Subtotal = VALUES(Subtotal),
    TotalAddOnAmount = VALUES(TotalAddOnAmount),
    GrandTotal = VALUES(GrandTotal),
    TransactionStatus = VALUES(TransactionStatus);

-- Transaction 10001: one medium Cappuccino with one Extra Shot.
-- Item total = 4.50 base + 1.00 size + 1.50 add-on = 7.00.
-- Transaction 10002: two small Hot Chocolates with one Whipped Cream total.
-- Item total = (4.00 base x 2) + 0.00 size + 1.00 add-on = 9.00.
INSERT INTO TRANSACTION_ITEMS
    (TransactionItemID, TransactionID, BeverageID, SizeID, Quantity,
     SugarLevel, IceLevel, TemperatureOption, BasePriceAtPurchase,
     SizePriceAtPurchase, AddOnAmount, ItemTotal)
VALUES
    (50001, 10001, 103, 2, 1, 'Normal', 'None', 'Hot', 4.50, 1.00, 1.50, 7.00),
    (50002, 10002, 201, 1, 1, 'Less', 'None', 'Hot', 4.00, 0.00, 1.00, 9.00)
ON DUPLICATE KEY UPDATE
    TransactionID = VALUES(TransactionID),
    BeverageID = VALUES(BeverageID),
    SizeID = VALUES(SizeID),
    Quantity = VALUES(Quantity),
    SugarLevel = VALUES(SugarLevel),
    IceLevel = VALUES(IceLevel),
    TemperatureOption = VALUES(TemperatureOption),
    BasePriceAtPurchase = VALUES(BasePriceAtPurchase),
    SizePriceAtPurchase = VALUES(SizePriceAtPurchase),
    AddOnAmount = VALUES(AddOnAmount),
    ItemTotal = VALUES(ItemTotal);


INSERT INTO TRANSACTION_ITEM_ADD_ONS
    (ItemAddOnID, TransactionItemID, AddOnID, AddOnPriceAtPurchase, Quantity, AddOnSubtotal)
VALUES
    (70001, 50001, 1, 1.50, 1, 1.50),
    (70002, 50002, 2, 1.00, 1, 1.00)
ON DUPLICATE KEY UPDATE
    AddOnPriceAtPurchase = VALUES(AddOnPriceAtPurchase),
    Quantity = VALUES(Quantity),
    AddOnSubtotal = VALUES(AddOnSubtotal);

COMMIT;

-- =========================================================
-- QUICK VERIFICATION
-- =========================================================
SELECT 'Categories' AS DataSet, COUNT(*) AS RowCount FROM CATEGORIES
UNION ALL
SELECT 'Beverages', COUNT(*) FROM BEVERAGES
UNION ALL
SELECT 'Size options', COUNT(*) FROM SIZE_OPTIONS
UNION ALL
SELECT 'Add-ons', COUNT(*) FROM ADD_ONS
UNION ALL
SELECT 'Payment methods', COUNT(*) FROM PAYMENT_METHODS
UNION ALL
SELECT 'Stock records', COUNT(*) FROM STOCK
UNION ALL
SELECT 'Sales transactions', COUNT(*) FROM SALES_TRANSACTIONS
UNION ALL
SELECT 'Transaction items', COUNT(*) FROM TRANSACTION_ITEMS
UNION ALL
SELECT 'Item add-ons', COUNT(*) FROM TRANSACTION_ITEM_ADD_ONS;
