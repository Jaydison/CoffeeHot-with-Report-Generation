CREATE DATABASE IF NOT EXISTS coffee_shop
    CHARACTER SET utf8mb4
    COLLATE utf8mb4_unicode_ci;

USE coffee_shop;


-- =========================================================
-- 1. ADMINISTRATORS
-- =========================================================

CREATE TABLE IF NOT EXISTS ADMINS
(
    AdminID INT UNSIGNED AUTO_INCREMENT,
    Username VARCHAR(50) NOT NULL,
    PasswordHash VARCHAR(255) NOT NULL,
    AdminName VARCHAR(100) NOT NULL,
    AdminStatus VARCHAR(10) NOT NULL DEFAULT 'Active',
    CreatedAt DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT PK_ADMINS
        PRIMARY KEY (AdminID),

    CONSTRAINT UQ_ADMINS_Username
        UNIQUE (Username),

    CONSTRAINT CHK_ADMINS_UsernameLength
        CHECK (CHAR_LENGTH(Username) BETWEEN 4 AND 50),

    CONSTRAINT CHK_ADMINS_AdminNameLength
        CHECK (CHAR_LENGTH(AdminName) BETWEEN 2 AND 100),

    CONSTRAINT CHK_ADMINS_Status
        CHECK (AdminStatus IN ('Active', 'Inactive'))
)
ENGINE = InnoDB;


-- =========================================================
-- 2. BEVERAGE CATEGORIES
-- =========================================================

CREATE TABLE IF NOT EXISTS CATEGORIES
(
    CategoryID INT UNSIGNED AUTO_INCREMENT,
    CategoryName VARCHAR(50) NOT NULL,
    CategoryDescription VARCHAR(255) NULL,
    CategoryStatus VARCHAR(10) NOT NULL DEFAULT 'Active',

    CONSTRAINT PK_CATEGORIES
        PRIMARY KEY (CategoryID),

    CONSTRAINT UQ_CATEGORIES_CategoryName
        UNIQUE (CategoryName),

    CONSTRAINT CHK_CATEGORIES_NameLength
        CHECK (CHAR_LENGTH(CategoryName) BETWEEN 2 AND 50),

    CONSTRAINT CHK_CATEGORIES_Status
        CHECK (CategoryStatus IN ('Active', 'Inactive'))
)
ENGINE = InnoDB;


-- =========================================================
-- 3. BEVERAGES
-- =========================================================

CREATE TABLE IF NOT EXISTS BEVERAGES
(
    BeverageID INT UNSIGNED AUTO_INCREMENT,
    CategoryID INT UNSIGNED NOT NULL,
    BeverageName VARCHAR(100) NOT NULL,
    BeverageDescription VARCHAR(255) NULL,
    BasePrice DECIMAL(8,2) UNSIGNED NOT NULL,
    BeverageStatus VARCHAR(15) NOT NULL DEFAULT 'Available',

    CONSTRAINT PK_BEVERAGES
        PRIMARY KEY (BeverageID),

    CONSTRAINT UQ_BEVERAGES_BeverageName
        UNIQUE (BeverageName),

    CONSTRAINT CHK_BEVERAGES_NameLength
        CHECK (CHAR_LENGTH(BeverageName) BETWEEN 2 AND 100),

    CONSTRAINT CHK_BEVERAGES_BasePrice
        CHECK (BasePrice BETWEEN 0.00 AND 999999.99),

    CONSTRAINT CHK_BEVERAGES_Status
        CHECK (
            BeverageStatus IN ('Available', 'Unavailable')
        ),

    CONSTRAINT FK_BEVERAGES_Category
        FOREIGN KEY (CategoryID)
        REFERENCES CATEGORIES (CategoryID)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
)
ENGINE = InnoDB;


-- =========================================================
-- 4. SIZE OPTIONS
-- =========================================================

CREATE TABLE IF NOT EXISTS SIZE_OPTIONS
(
    SizeID INT UNSIGNED AUTO_INCREMENT,
    SizeName VARCHAR(20) NOT NULL,
    AdditionalPrice DECIMAL(6,2) UNSIGNED NOT NULL DEFAULT 0.00,
    SizeStatus VARCHAR(10) NOT NULL DEFAULT 'Active',

    CONSTRAINT PK_SIZE_OPTIONS
        PRIMARY KEY (SizeID),

    CONSTRAINT UQ_SIZE_OPTIONS_SizeName
        UNIQUE (SizeName),

    CONSTRAINT CHK_SIZE_OPTIONS_Name
        CHECK (SizeName IN ('Small', 'Medium', 'Large')),

    CONSTRAINT CHK_SIZE_OPTIONS_AdditionalPrice
        CHECK (AdditionalPrice BETWEEN 0.00 AND 9999.99),

    CONSTRAINT CHK_SIZE_OPTIONS_Status
        CHECK (SizeStatus IN ('Active', 'Inactive'))
)
ENGINE = InnoDB;


-- =========================================================
-- 5. ADD-ONS
-- =========================================================

CREATE TABLE IF NOT EXISTS ADD_ONS
(
    AddOnID INT UNSIGNED AUTO_INCREMENT,
    AddOnName VARCHAR(50) NOT NULL,
    AddOnPrice DECIMAL(6,2) UNSIGNED NOT NULL DEFAULT 0.00,
    AddOnStatus VARCHAR(10) NOT NULL DEFAULT 'Active',

    CONSTRAINT PK_ADD_ONS
        PRIMARY KEY (AddOnID),

    CONSTRAINT UQ_ADD_ONS_AddOnName
        UNIQUE (AddOnName),

    CONSTRAINT CHK_ADD_ONS_NameLength
        CHECK (CHAR_LENGTH(AddOnName) BETWEEN 2 AND 50),

    CONSTRAINT CHK_ADD_ONS_Price
        CHECK (AddOnPrice BETWEEN 0.00 AND 9999.99),

    CONSTRAINT CHK_ADD_ONS_Status
        CHECK (AddOnStatus IN ('Active', 'Inactive'))
)
ENGINE = InnoDB;


-- =========================================================
-- 6. PAYMENT METHODS
-- =========================================================

CREATE TABLE IF NOT EXISTS PAYMENT_METHODS
(
    PaymentMethodID INT UNSIGNED AUTO_INCREMENT,
    PaymentMethodName VARCHAR(30) NOT NULL,
    PaymentStatus VARCHAR(10) NOT NULL DEFAULT 'Active',

    CONSTRAINT PK_PAYMENT_METHODS
        PRIMARY KEY (PaymentMethodID),

    CONSTRAINT UQ_PAYMENT_METHODS_Name
        UNIQUE (PaymentMethodName),

    CONSTRAINT CHK_PAYMENT_METHODS_NameLength
        CHECK (
            CHAR_LENGTH(PaymentMethodName) BETWEEN 2 AND 30
        ),

    CONSTRAINT CHK_PAYMENT_METHODS_Status
        CHECK (PaymentStatus IN ('Active', 'Inactive'))
)
ENGINE = InnoDB;


-- =========================================================
-- 7. SALES TRANSACTIONS
-- =========================================================

CREATE TABLE IF NOT EXISTS SALES_TRANSACTIONS
(
    TransactionID INT UNSIGNED AUTO_INCREMENT,
    PaymentMethodID INT UNSIGNED NOT NULL,
    TransactionTimestamp DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    Subtotal DECIMAL(10,2) UNSIGNED NOT NULL,
    TotalAddOnAmount DECIMAL(10,2) UNSIGNED NOT NULL DEFAULT 0.00,
    GrandTotal DECIMAL(10,2) UNSIGNED NOT NULL,
    TransactionStatus VARCHAR(15) NOT NULL DEFAULT 'Pending',

    CONSTRAINT PK_SALES_TRANSACTIONS
        PRIMARY KEY (TransactionID),

    CONSTRAINT CHK_SALES_TRANSACTIONS_Subtotal
        CHECK (Subtotal BETWEEN 0.00 AND 99999999.99),

    CONSTRAINT CHK_SALES_TRANSACTIONS_AddOnAmount
        CHECK (TotalAddOnAmount BETWEEN 0.00 AND 99999999.99),

    CONSTRAINT CHK_SALES_TRANSACTIONS_GrandTotal
        CHECK (GrandTotal BETWEEN 0.00 AND 99999999.99),

    CONSTRAINT CHK_SALES_TRANSACTIONS_Status
        CHECK (
            TransactionStatus IN (
                'Pending',
                'Completed',
                'Cancelled'
            )
        ),

    CONSTRAINT FK_SALES_TRANSACTIONS_PaymentMethod
        FOREIGN KEY (PaymentMethodID)
        REFERENCES PAYMENT_METHODS (PaymentMethodID)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
)
ENGINE = InnoDB;


-- =========================================================
-- 8. TRANSACTION ITEMS
-- =========================================================

CREATE TABLE IF NOT EXISTS TRANSACTION_ITEMS
(
    TransactionItemID INT UNSIGNED AUTO_INCREMENT,
    TransactionID INT UNSIGNED NOT NULL,
    BeverageID INT UNSIGNED NOT NULL,
    SizeID INT UNSIGNED NOT NULL,
    Quantity INT UNSIGNED NOT NULL,
    SugarLevel VARCHAR(15) NOT NULL DEFAULT 'Normal',
    IceLevel VARCHAR(15) NOT NULL DEFAULT 'Normal',
    TemperatureOption VARCHAR(10) NOT NULL,
    BasePriceAtPurchase DECIMAL(8,2) UNSIGNED NOT NULL,
    SizePriceAtPurchase DECIMAL(6,2) UNSIGNED NOT NULL DEFAULT 0.00,
    AddOnAmount DECIMAL(8,2) UNSIGNED NOT NULL DEFAULT 0.00,
    ItemTotal DECIMAL(10,2) UNSIGNED NOT NULL,

    CONSTRAINT PK_TRANSACTION_ITEMS
        PRIMARY KEY (TransactionItemID),

    CONSTRAINT CHK_TRANSACTION_ITEMS_Quantity
        CHECK (Quantity BETWEEN 1 AND 99),

    CONSTRAINT CHK_TRANSACTION_ITEMS_SugarLevel
        CHECK (
            SugarLevel IN ('None', 'Less', 'Normal', 'Extra')
        ),

    CONSTRAINT CHK_TRANSACTION_ITEMS_IceLevel
        CHECK (
            IceLevel IN ('None', 'Less', 'Normal', 'Extra')
        ),

    CONSTRAINT CHK_TRANSACTION_ITEMS_Temperature
        CHECK (TemperatureOption IN ('Hot', 'Cold')),

    CONSTRAINT CHK_TRANSACTION_ITEMS_BasePrice
        CHECK (
            BasePriceAtPurchase BETWEEN 0.00 AND 999999.99
        ),

    CONSTRAINT CHK_TRANSACTION_ITEMS_SizePrice
        CHECK (
            SizePriceAtPurchase BETWEEN 0.00 AND 9999.99
        ),

    CONSTRAINT CHK_TRANSACTION_ITEMS_AddOnAmount
        CHECK (AddOnAmount BETWEEN 0.00 AND 999999.99),

    CONSTRAINT CHK_TRANSACTION_ITEMS_ItemTotal
        CHECK (ItemTotal BETWEEN 0.00 AND 99999999.99),

    CONSTRAINT FK_TRANSACTION_ITEMS_Transaction
        FOREIGN KEY (TransactionID)
        REFERENCES SALES_TRANSACTIONS (TransactionID)
        ON UPDATE CASCADE
        ON DELETE CASCADE,

    CONSTRAINT FK_TRANSACTION_ITEMS_Beverage
        FOREIGN KEY (BeverageID)
        REFERENCES BEVERAGES (BeverageID)
        ON UPDATE CASCADE
        ON DELETE RESTRICT,

    CONSTRAINT FK_TRANSACTION_ITEMS_Size
        FOREIGN KEY (SizeID)
        REFERENCES SIZE_OPTIONS (SizeID)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
)
ENGINE = InnoDB;


-- =========================================================
-- 9. TRANSACTION ITEM ADD-ONS
-- =========================================================

CREATE TABLE IF NOT EXISTS TRANSACTION_ITEM_ADD_ONS
(
    ItemAddOnID INT UNSIGNED AUTO_INCREMENT,
    TransactionItemID INT UNSIGNED NOT NULL,
    AddOnID INT UNSIGNED NOT NULL,
    AddOnPriceAtPurchase DECIMAL(6,2) UNSIGNED NOT NULL,
    Quantity INT UNSIGNED NOT NULL,
    AddOnSubtotal DECIMAL(8,2) UNSIGNED NOT NULL,

    CONSTRAINT PK_TRANSACTION_ITEM_ADD_ONS
        PRIMARY KEY (ItemAddOnID),

    CONSTRAINT UQ_TRANSACTION_ITEM_ADD_ONS
        UNIQUE (TransactionItemID, AddOnID),

    CONSTRAINT CHK_TRANSACTION_ITEM_ADD_ONS_Price
        CHECK (
            AddOnPriceAtPurchase BETWEEN 0.00 AND 9999.99
        ),

    CONSTRAINT CHK_TRANSACTION_ITEM_ADD_ONS_Quantity
        CHECK (Quantity BETWEEN 1 AND 10),

    CONSTRAINT CHK_TRANSACTION_ITEM_ADD_ONS_Subtotal
        CHECK (AddOnSubtotal BETWEEN 0.00 AND 999999.99),

    CONSTRAINT FK_TRANSACTION_ITEM_ADD_ONS_Item
        FOREIGN KEY (TransactionItemID)
        REFERENCES TRANSACTION_ITEMS (TransactionItemID)
        ON UPDATE CASCADE
        ON DELETE CASCADE,

    CONSTRAINT FK_TRANSACTION_ITEM_ADD_ONS_AddOn
        FOREIGN KEY (AddOnID)
        REFERENCES ADD_ONS (AddOnID)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
)
ENGINE = InnoDB;


-- =========================================================
-- 10. BEVERAGE STOCK
-- =========================================================

CREATE TABLE IF NOT EXISTS STOCK
(
    StockID INT UNSIGNED AUTO_INCREMENT,
    BeverageID INT UNSIGNED NOT NULL,
    QuantityAvailable INT UNSIGNED NOT NULL DEFAULT 0,
    LowStockLevel INT UNSIGNED NOT NULL DEFAULT 5,
    LastUpdated DATETIME NOT NULL
        DEFAULT CURRENT_TIMESTAMP
        ON UPDATE CURRENT_TIMESTAMP,
    UpdatedBy INT UNSIGNED NOT NULL,

    CONSTRAINT PK_STOCK
        PRIMARY KEY (StockID),

    CONSTRAINT UQ_STOCK_BeverageID
        UNIQUE (BeverageID),

    CONSTRAINT CHK_STOCK_Quantity
        CHECK (QuantityAvailable BETWEEN 0 AND 99999),

    CONSTRAINT CHK_STOCK_LowStockLevel
        CHECK (LowStockLevel BETWEEN 0 AND 99999),

    CONSTRAINT FK_STOCK_Beverage
        FOREIGN KEY (BeverageID)
        REFERENCES BEVERAGES (BeverageID)
        ON UPDATE CASCADE
        ON DELETE RESTRICT,

    CONSTRAINT FK_STOCK_Admin
        FOREIGN KEY (UpdatedBy)
        REFERENCES ADMINS (AdminID)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
)
ENGINE = InnoDB;