package com.staniskhan.todolist.tasks;

public class Task
{
    private Long ID;
    private String title;
    private String description;
    private String status;

    public Task(Long ID,
                String title,
                String description,
                String status)
    {
        this.setID(ID);
        this.setTitle(title);
        this.setDescription(description);
        this.setStatus(status);
    }

    public Long getID() {
        return ID;
    }

    public void setID(Long ID) {
        this.ID = ID;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
}
