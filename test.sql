CREATE TABLE test(
  id INT NOT NULL AUTO_INCREMENT,
  first_name VARCHAR(100) NOT NULL,
  last_name VARCHAR(100) NOT NULL,
  PRIMARY KEY (id)
);

INSERT INTO test (first_name, last_name) VALUES 
    ('Robin', 'Jackman'),
    ('Taylor', 'Edward'),
    ('Vivian', 'Dickens'),
    ('Harry', 'Clifford'),
    ('Eliza', 'Clifford'),
    ('Nancy', 'Newman'),
    ('Melinda', 'Clifford');