package com.staniskhan.todolist;

import com.staniskhan.todolist.tasks.Task;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@SpringBootApplication
public class ToDoListApplication {

    public static void main(String[] args) {
        SpringApplication.run(ToDoListApplication.class, args);
    }

    @GetMapping
    public List<Task> helloWorld()
    {
        return List.of(
                new Task(1L,
                        "Купить молоко",
                        "Обязательно 3.2% жирности",
                        "todo"),
                new Task(2L,
                        "Купить молоко2",
                        "Обязательно 3.2% жирности2",
                        "todo2"));
    }
}
